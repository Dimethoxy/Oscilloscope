#pragma once
#include <JuceHeader.h>

template<typename T>
class RingBuffer
{
public:
  RingBuffer(const int bufferSize, const int numChannels)
    : bufferSize(bufferSize)
    , numChannels(numChannels)
    , position(0)
    , buffer(std::make_unique<AudioBuffer<T>>(numChannels, bufferSize))
  {
  }

  const AudioBuffer<T> read() const noexcept {}
  void write(const AudioBuffer<T> bufferToWrite) {}

private:
  const int bufferSize;
  const int numChannels;
  juce::Atomic<int> position;
  std::unique_ptr<AudioBuffer<T>> buffer;
};