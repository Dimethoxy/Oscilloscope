#pragma once
//==============================================================================
<<<<<<< HEAD
=======
#include "AhdEnvelopeParameters.h"
#include "DigitalOscillatorParameters.h"
>>>>>>> a5e5c670fddd956080480f24e1397fa5872f9993
#include <JuceHeader.h>
//==============================================================================
namespace dmt {
namespace model {
//==============================================================================
static inline juce::AudioProcessorParameterGroup
<<<<<<< HEAD
neutrinoParameterGroup(juce::String parentUid, int versionHint)
{
  using ParameterInt = juce::AudioParameterInt;
  using ParameterFloat = juce::AudioParameterFloat;
  // using ParameterChoice = juce::AudioParameterChoice;
  using NormalisableRange = juce::NormalisableRange<float>;
=======
neutrinoParameterGroup(juce::String parentUid, [[maybe_unused]] int versionHint)
{
  using ParameterInt = juce::AudioParameterInt;
  using ParameterFloat = juce::AudioParameterFloat;
  using ParameterChoice = juce::AudioParameterChoice;
  using NormalisableRange = juce::NormalisableRange<float>;
  using ParameterGroup = juce::AudioProcessorParameterGroup;
>>>>>>> a5e5c670fddd956080480f24e1397fa5872f9993

  juce::String uid = parentUid + "Neutrino";

  return juce::AudioProcessorParameterGroup(
    uid,        // group ID
    "Neutrino", // group name
    "|",        // separator

<<<<<<< HEAD
    // Symmetry
    std::make_unique<ParameterFloat>(uid + "Symmetry",
                                     "Symmetry",
                                     NormalisableRange(-1.f, // rangeStart
                                                       1.f,  // rangeEnd
                                                       .01f, // intervalValue
                                                       1.f), // skewFactor
                                     .0f));
=======
    // Oscillators
    std::make_unique<ParameterGroup>(digitalOscillatorParameterGroup(uid)),

    // Envelopes
    std::make_unique<ParameterGroup>(envelopeParameterGroup(
      uid, "Gain", { 0.0f, 0.055f, 0.350f, 0.0f, 0.0f, 0.0f })),
    std::make_unique<ParameterGroup>(envelopeParameterGroup(
      uid, "Pitch1", { 0.0f, 0.0f, 0.185f, 0.033f, 0.0f, 0.0f })),
    std::make_unique<ParameterGroup>(envelopeParameterGroup(
      uid, "Pitch2", { 0.0f, 0.0f, 0.02f, 0.033f, 0.0f, 0.0f })));
>>>>>>> a5e5c670fddd956080480f24e1397fa5872f9993
}
} // namespace model
} // namespace dmt