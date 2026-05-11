//==============================================================================
/* ██████╗ ██╗███╗   ███╗███████╗████████╗██╗  ██╗ ██████╗ ██╗  ██╗██╗   ██╗
 * ██╔══██╗██║████╗ ████║██╔════╝╚══██╔══╝██║  ██║██╔═══██╗╚██╗██╔╝╚██╗ ██╔╝
 * ██║  ██║██║██╔████╔██║█████╗     ██║   ███████║██║   ██║ ╚███╔╝  ╚████╔╝
 * ██║  ██║██║██║╚██╔╝██║██╔══╝     ██║   ██╔══██║██║   ██║ ██╔██╗   ╚██╔╝
 * ██████╔╝██║██║ ╚═╝ ██║███████╗   ██║   ██║  ██║╚██████╔╝██╔╝ ██╗   ██║
 * ╚═════╝ ╚═╝╚═╝     ╚═╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝
 * Copyright (C) 2024 Dimethoxy Audio (https://dimethoxy.com)
 *
 * Part of the Dimethoxy Library, primarily intended for Dimethoxy plugins.
 * External use is permitted but not recommended.
 * No support or compatibility guarantees are provided.
 *
 * License:
 * This code is licensed under the GPLv3 license. You are permitted to use and
 * modify this code under the terms of this license.
 * You must adhere GPLv3 license for any project using this code or parts of it.
 * Your are not allowed to use this code in any closed-source project.
 *
 * Description:
 * OscillatorPanel is a GUI component that provides controls for oscillator
 * settings.
 *
 * Authors:
 * Lunix-420 (Primary Author)
 */
//==============================================================================

#pragma once

//==============================================================================

#include "gui/panel/AbstractPanel.h"
<<<<<<< HEAD
#include "gui/panel/AnalogOscillatorPanel.h"
=======
>>>>>>> a5e5c670fddd956080480f24e1397fa5872f9993
#include "gui/panel/Carousel.h"
#include "gui/panel/ModernOscillatorPanel.h"
#include <JuceHeader.h>

//==============================================================================

namespace dmt {
namespace gui {
namespace panel {

//==============================================================================
class OscillatorPanel : public dmt::gui::panel::Carousel
{
public:
  OscillatorPanel()
    : Carousel()
  {
<<<<<<< HEAD
    panels.push_back(std::make_unique<AnalogOscillatorPanel>());
=======
>>>>>>> a5e5c670fddd956080480f24e1397fa5872f9993
    panels.push_back(std::make_unique<ModernOscillatorPanel>());
    init();
  }

private:
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorPanel)
};
//==============================================================================
} // namespace panels
} // namespace gui
} // namespace dmt
