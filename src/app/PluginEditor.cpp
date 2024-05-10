#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : AudioProcessorEditor(&p)
  , p(p)
{
  openGLContext.setComponentPaintingEnabled(true);
  openGLContext.setContinuousRepainting(false);
  openGLContext.attachTo(*getTopLevelComponent());

  setSize(800, 400);
  setResizable(true, true);
  setResizeLimits(100, 50, 4000, 2000);
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
}
