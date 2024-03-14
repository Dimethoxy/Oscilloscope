#pragma once

#include "../../external/dmt/gui/panel/OscilloscopePanel.h"
#include "PluginProcessor.h"

//==============================================================================
class PluginEditor final : public juce::AudioProcessorEditor
{
public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

private:
  PluginProcessor& p;
  dmt::gui::panel::OscilloscopePanel mainEditor;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
