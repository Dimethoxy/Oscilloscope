#pragma once

#include "OscilloscopePanel.h"
#include "PluginProcessor.h"

//==============================================================================
class ProcessorEditor final : public juce::AudioProcessorEditor
{
public:
  explicit ProcessorEditor(AudioPluginAudioProcessor&);
  ~ProcessorEditor() override;

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

private:
  AudioPluginAudioProcessor& p;
  OscilloscopePanel mainEditor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
