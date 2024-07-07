#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : AudioProcessorEditor(&p)
  , p(p)
  , oscilloscopePanel(p.oscilloscopeFifo, p.apvts)
{
  addAndMakeVisible(oscilloscopePanel);
  setSize(baseWidth, baseHeight);
  setResizable(true, true);
  setResizeLimits(200, 100, 4000, 1000);

  openGLContext.setComponentPaintingEnabled(true);
  openGLContext.setContinuousRepainting(false);
  openGLContext.attachTo(*getTopLevelComponent());
}

PluginEditor::~PluginEditor() {}

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
  const auto bounds = getLocalBounds();
  const auto height = bounds.getHeight();
  size = (float)height / (float)baseHeight;
  oscilloscopePanel.setBounds(bounds);
}
