#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : dmt::app::AbstractPluginEditor(
      p,
      "Oscilloscope",
      dmt::app::AbstractPluginEditor::WindowConfig{
        700,
        400,
        dmt::app::AbstractPluginEditor::WindowMode::Dynamic,
        0.5f,
        2.0f,
        16.0f / 9.0f,
        64.0f / 9.0f },
      [&p](dmt::gui::window::Layout& layout) {
        layout.addPanel<dmt::gui::panel::OscilloscopePanel<float>>(
          0, 0, 1, 1, p.oscilloscopeBuffer, p.apvts);
      })
{
}

//==============================================================================
PluginEditor::~PluginEditor() {}