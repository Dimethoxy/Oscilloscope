#pragma once

#include "PluginProcessor.h"
#include <DmtHeader.h>

//==============================================================================
class PluginEditor final : public juce::AudioProcessorEditor
{
  using Image = juce::Image;
  using ImageComponent = juce::ImageComponent;
  using PixelFormat = juce::Image::PixelFormat;
  using OpenGLContext = juce::OpenGLContext;

  // Window size
  float& size = dmt::Settings::Window::size;
  const int baseWidth = 900;
  const int baseHeight = 500;

public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;

private:
  //==============================================================================
  PluginProcessor& p;
  OpenGLContext openGLContext;
  //==============================================================================

  int lastWidth = baseWidth;
  int lastHeight = baseHeight;
  double ratio = baseWidth / baseHeight;
  //==============================================================================
  Image image;
  bool isResizing = false;
  //==============================================================================
  dmt::gui::panel::OscilloscopePanel<float> oscilloscopePanel;
  dmt::gui::window::Compositor compositor;
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
