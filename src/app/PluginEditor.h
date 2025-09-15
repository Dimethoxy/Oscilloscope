#pragma once

#include "PluginProcessor.h"
#include <DmtHeader.h>

//==============================================================================
class PluginEditor
  : public juce::AudioProcessorEditor
  , private juce::Timer
{
  using Image = juce::Image;
  using ImageComponent = juce::ImageComponent;
  using PixelFormat = juce::Image::PixelFormat;
  using OpenGLContext = juce::OpenGLContext;

  // Window size
  const int baseWidth = 800;
  const int baseHeight = 450;

  // Window header
  const int& headerHeight = dmt::Settings::Header::height;

public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  //==============================================================================
  void paint(juce::Graphics&) override;
  void resized() override;
  void setConstraints(int width, int height);
  void handleHeaderVisibilityChange(bool isHeaderVisible);

  // Debounced resizing
  void timerCallback() override;
  void detachCompositorForResize();
  void attachCompositorAfterResize();
  void updateCompositorSnapshot();

private:
  //==============================================================================
  PluginProcessor& p;
  OpenGLContext openGLContext;
  //==============================================================================

  int lastWidth = baseWidth;
  int lastHeight = baseHeight;
  double ratio = baseWidth / baseHeight;
  float& sizeFactor = p.scaleFactor;
  //==============================================================================
  Image image;
  bool isResizing = false;
  //==============================================================================
  dmt::gui::panel::OscilloscopePanel<float> oscilloscopePanel;
  dmt::gui::window::Compositor compositor;
  //==============================================================================
  juce::Image compositorSnapshot;
  bool compositorAttached = true;
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
