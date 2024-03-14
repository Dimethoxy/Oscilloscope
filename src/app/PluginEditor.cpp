#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : AudioProcessorEditor(&p)
  , p(p)
{
  setSize(400, 300);
}

PluginEditor::~PluginEditor() {}

//==============================================================================
void
PluginEditor::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::green);
}

void
PluginEditor::resized()
{
}
