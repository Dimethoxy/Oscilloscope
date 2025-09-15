#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : AudioProcessorEditor(&p)
  , p(p)
  , sizeFactor(p.scaleFactor)
  , mainLayout({ 1.0 }, { 1.0 })
  , compositor("OscilloScoPe", mainLayout, p.apvts, p.properties, sizeFactor)
  , compositorAttached(true)
{
  if (OS_IS_WINDOWS) {
    setResizable(true, true);
  }

  if (OS_IS_DARWIN) {
    setResizable(true, true);
  }

  if (OS_IS_LINUX) {
    openGLContext.setComponentPaintingEnabled(true);
    openGLContext.setContinuousRepainting(false);
    openGLContext.attachTo(*getTopLevelComponent());
    setResizable(true, true);
  }
  // Add Panel to Layout
  mainLayout.addPanel<dmt::gui::panel::OscilloscopePanel<float>>(
    0, 0, 1, 1, p.oscilloscopeFifo, p.apvts);

  setConstraints(baseWidth, baseHeight + headerHeight);
  addAndMakeVisible(compositor);
  setResizable(true, true);

  const auto startWidth = baseWidth * sizeFactor;
  const auto startHeight = (baseHeight + headerHeight) * sizeFactor;
  setSize(startWidth, startHeight);

  // Set the callback for header visibility changes
  compositor.setHeaderVisibilityCallback([this](bool isHeaderVisible) {
    handleHeaderVisibilityChange(isHeaderVisible);
  });
}

void
PluginEditor::handleHeaderVisibilityChange(bool isHeaderVisible)
{
  const int adjustedHeight =
    isHeaderVisible ? baseHeight + headerHeight : baseHeight;
  setConstraints(baseWidth, adjustedHeight);
  setSize(baseWidth * sizeFactor, adjustedHeight * sizeFactor);
}
//==============================================================================
PluginEditor::~PluginEditor() {}

//==============================================================================
void
PluginEditor::paint(juce::Graphics& g)
{
  TRACER("PluginEditor::paint");

  // Just painting the background
  g.fillAll(dmt::Settings::Window::backgroundColour);

  if (!compositorAttached && compositorSnapshot.isValid()) {
    // Draw the last compositor snapshot, scaled to fit
    auto bounds = getLocalBounds().toFloat();
    g.drawImage(
      compositorSnapshot, bounds, juce::RectanglePlacement::stretchToFit);
    return;
  }
}

//==============================================================================
void
PluginEditor::setConstraints(int width, int height)
{
  if (auto* constrainer = this->getConstrainer()) {
    const auto aspectRatio = (double)width / (double)height;
    constrainer->setFixedAspectRatio(aspectRatio);
    const auto minWidth = width / 2;
    const auto minHeight = height / 2;
    const auto maxWidth = width * 2;
    const auto maxHeight = height * 2;
    constrainer->setSizeLimits(minWidth, minHeight, maxWidth, maxHeight);
  } else {
    jassertfalse; // Constrainer not set
  }
}

//==============================================================================
void
PluginEditor::resized()
{
  TRACER("PluginEditor::resized");

  // Set the global size
  const int currentHeight = getHeight();
  const float newSize =
    (float)currentHeight /
    (compositor.isHeaderVisible() ? baseHeight + headerHeight : baseHeight);

  // Make sure the size makes sense
  if (newSize <= 0.0f || std::isinf(newSize)) {
    jassertfalse;
  }

  // Update the processor's scale factor
  sizeFactor = newSize;
  p.setScaleFactor(newSize);

  // Debounced resizing logic
  static bool firstDraw = true;
  if (firstDraw) {
    // On first draw, skip debounce and just layout normally
    compositor.setBounds(getLocalBounds());
    firstDraw = false;
    return;
  }
  detachCompositorForResize();
}

void
PluginEditor::detachCompositorForResize()
{
  if (compositorAttached) {
    // Take a snapshot before detaching
    updateCompositorSnapshot();

    // Remove compositor from view
    removeChildComponent(&compositor);
    compositorAttached = false;
  }

  // Restart debounce timer (100ms)
  stopTimer();
  startTimer(100);
}

void
PluginEditor::attachCompositorAfterResize()
{
  if (!compositorAttached) {
    // Snap to the correct aspect ratio, considering header visibility
    auto bounds = getLocalBounds();
    bool headerVisible = compositor.isHeaderVisible();
    int aspectHeight = headerVisible ? (baseHeight + headerHeight) : baseHeight;
    const double aspect = (double)baseWidth / (double)aspectHeight;
    int w = bounds.getWidth();
    int h = bounds.getHeight();
    double currentAspect = (double)w / (double)h;

    if (currentAspect > aspect) {
      // Too wide, adjust width
      w = static_cast<int>(h * aspect);
    } else if (currentAspect < aspect) {
      // Too tall, adjust height
      h = static_cast<int>(w / aspect);
    }
    setSize(w, h);

    // Set compositor bounds to fill the editor
    addAndMakeVisible(compositor);
    compositor.setBounds(getLocalBounds());
    compositorAttached = true;
    repaint();
  }
}

void
PluginEditor::updateCompositorSnapshot()
{
  // Render compositor to an image at its current size
  if (getWidth() > 0 && getHeight() > 0) {
    compositorSnapshot =
      juce::Image(juce::Image::ARGB, getWidth(), getHeight(), true);
    juce::Graphics g(compositorSnapshot);
    compositor.paintEntireComponent(g, true);
  }
}

void
PluginEditor::timerCallback()
{
  // Timer expired: reattach compositor and repaint
  stopTimer();
  attachCompositorAfterResize();
  repaint();
}
