#pragma once

#include "PluginProcessor.h"
#include <DmtHeader.h>

//==============================================================================
class PluginEditor final : public juce::AudioProcessorEditor
{
  float& size = dmt::Settings::Layout::size;

public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

private:
  int baseWidth = 800;
  int baseHeight = 400;
  PluginProcessor& p;
  dmt::gui::panel::OscilloscopePanel<float> oscilloscopePanel;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
