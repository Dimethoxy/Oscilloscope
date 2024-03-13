#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
ProcessorEditor::ProcessorEditor(AudioPluginAudioProcessor& p)
  : AudioProcessorEditor(&p)
  , p(p)
{
  setSize(400, 300);
}

ProcessorEditor::~ProcessorEditor() {}

//==============================================================================
void
AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
  g.fillAll(juce::Colours::green);
}

void
AudioPluginAudioProcessorEditor::resized()
{
}
