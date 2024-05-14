#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : AudioProcessorEditor(&p)
  , p(p)
  , oscilloscopePanel(p.oscilloscopeFifo)
{
  addAndMakeVisible(oscilloscopePanel);
  setSize(800, 400);
  setResizable(true, true);
  setResizeLimits(100, 50, 4000, 2000);
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
  auto bounds = getLocalBounds();
  oscilloscopePanel.setBounds(bounds);
}
