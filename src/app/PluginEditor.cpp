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
  setResizeLimits(200, 100, 4000, 2000);
}

PluginEditor::~PluginEditor() {}

//==============================================================================
void
PluginEditor::paint(juce::Graphics& g)
{
  g.fillAll(dmt::Settings::Colours::background);
}

//==============================================================================
void
PluginEditor::resized()
{
  const auto bounds = getLocalBounds();
  const auto height = bounds.getHeight();
  const auto width = bounds.getWidth();
  size = (float)height / (float)baseHeight;
  oscilloscopePanel.setBounds(bounds);
}
