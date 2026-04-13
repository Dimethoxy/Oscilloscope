#include "PluginEditor.h"
#include "PluginProcessor.h"

//==============================================================================
PluginEditor::PluginEditor(PluginProcessor& p)
  : dmt::app::AbstractPluginEditor(
      p,
      "Oscilloscope",
      800,
      400,
      [&p](dmt::gui::window::Layout& layout) {
        layout.addPanel<dmt::gui::panel::OscilloscopePanel<float>>(
          0, 0, 1, 1, p.apvts, p.oscilloscopeBuffer);
      })
{
}

//==============================================================================
PluginEditor::~PluginEditor() {}
