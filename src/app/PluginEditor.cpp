#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : AudioProcessorEditor(&p)
  , p(p)
  , oscilloscopePanel(p.oscilloscopeFifo, p.apvts)
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
    setResizable(false, true);
  }

  auto& lnf = this->getLookAndFeel();
  lnf.setUsingNativeAlertWindows(true);
  lnf.setColour(juce::ResizableWindow::backgroundColourId,
                dmt::Settings::Colours::background);
  // this->getTopLevelComponent();

  addAndMakeVisible(imageComponent);
  imageComponent.setVisible(false);
  addAndMakeVisible(oscilloscopePanel);
  setSize(baseWidth, baseHeight);
}
//==============================================================================
PluginEditor::~PluginEditor() {}

//==============================================================================
void
PluginEditor::timerCallback()
{
  stopTimer();
  TRACER("PluginEditor::timerCallback");
  const auto bounds = getLocalBounds();
  const auto height = bounds.getHeight();
  size = (float)height / (float)baseHeight;
  oscilloscopePanel.setBounds(bounds);
  addAndMakeVisible(oscilloscopePanel);
  imageComponent.setVisible(false);
}

//==============================================================================
void
PluginEditor::paint(juce::Graphics& g)
{
  TRACER("PluginEditor::paint");

  g.fillAll(dmt::Settings::Colours::background);
}

//==============================================================================
void
PluginEditor::resized()
{
  TRACER("PluginEditor::resized");

  // Let's cache this component's graphics to an image
  if (!imageComponent.isVisible()) {
    const int width = jmax(1, getWidth());
    const int height = jmax(1, getHeight());
    image = Image(PixelFormat::ARGB, width, height, true);
    juce::Graphics graphics(image);
    paint(graphics);
  }

  imageComponent.setImage(image);
  imageComponent.setVisible(true);
  imageComponent.setBounds(getLocalBounds());
  imageComponent.setAlwaysOnTop(true);

  // We remove all children to improve resize performance
  removeAllChildren();

  // We start a timer to add the children back after resizing
  stopTimer();
  startTimer(100);

  repaint();
}
void
PluginEditor::parentSizeChanged()
{
  TRACER("PluginEditor::parentSizeChanged");
}