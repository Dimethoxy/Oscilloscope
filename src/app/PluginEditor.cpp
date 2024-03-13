#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(
  AudioPluginAudioProcessor& p)
  : AudioProcessorEditor(&p)
  , processorRef(p)
{
  setSize(400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

//==============================================================================
void
AudioPluginAudioProcessorEditor::paint(juce::Graphics& g)
{
}

void
AudioPluginAudioProcessorEditor::resized()
{
}
