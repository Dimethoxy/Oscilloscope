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

  const AudioBuffer<T> read(AudioBuffer<T>& targetBuffer) const noexcept
  {
    while (!accessMutex.tryEnter())
      std::this_thread::yield();

    const int startingPosition = position.get();
    for (int sample = 0; sample < bufferSize; ++sample) {

      const int ringPosition = (startingPosition + sample) % bufferSize;

      for (int channel = 0; channel < numChannels; ++channel) {
        targetBuffer.copyFrom(
          channel, sample, *buffer, channel, ringPosition, 1);
      }
    }
  }

  void write(const AudioBuffer<T> bufferToWrite)
  {
    // juce::CriticalSection::ScopedLockType lock(accessMutex);
    //  copy data from bufferToWrite to buffer
  }

private:
  const int bufferSize;
  const int numChannels;
  juce::Atomic<AtomicHelpers::DiffTypeHelper<int>::Type> position;
  std::unique_ptr<AudioBuffer<T>> buffer;
  mutable juce::CriticalSection accessMutex;
};