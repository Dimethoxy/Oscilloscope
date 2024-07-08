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
    setResizable(true, true);
  }

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

  // We remove all children to improve resize performance
  removeAllChildren();

  // We start a timer to add the children back after resizing
  stopTimer();
  startTimer(500);
}
void
PluginEditor::parentSizeChanged()
{
  TRACER("PluginEditor::parentSizeChanged");
}