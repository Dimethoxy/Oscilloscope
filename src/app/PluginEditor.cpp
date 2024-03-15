#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : AudioProcessorEditor(&p)
  , p(p)
  , oscilloscopePanel(p.oscilloscopeProcessor)
{
  addAndMakeVisible(oscilloscopePanel);
  setSize(600, 300);
}

PluginEditor::~PluginEditor() {}

//==============================================================================
void
PluginEditor::paint(juce::Graphics& g)
{
  g.fillAll(dmt::LibrarySettings::Colours::background);
}

void
PluginEditor::resized()
{
  oscilloscopePanel.setBounds(getLocalBounds());
}
