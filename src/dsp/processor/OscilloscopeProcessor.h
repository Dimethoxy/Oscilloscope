
//==============================================================================
#pragma once
//==============================================================================
#include "../data/RingBuffer.h"
#include <JuceHeader.h>
//==============================================================================
namespace dmt {
namespace dsp {
namespace processor {
//==============================================================================
template<typename SampleType>
class OscilloscopeProcessor : public juce::AudioProcessor
{
  using RingBuffer = dmt::dsp::data::RingBuffer<SampleType>;

public:
  //============================================================================
  void prepareToPlay(double sampleRate, int samplesPerBlock)
  {
    ringBuffer = std::make_unique<RingBuffer>(2, sampleRate);
  }
  void processBlock(juce::AudioBuffer<SampleType>& buffer,
                    juce::MidiBuffer& midiMessages)
  {
    juce::AudioBuffer<SampleType> bufferCopy(buffer);
    bufferQueue.push(bufferCopy);
  }
  void consumeQueue()
  {
    while (true) {
      std::unique_lock<std::mutex> lock(mtx);

      // Wait until the queue is not empty
      queueConditionVariable.wait(lock, [] { return !bufferQueue.empty(); });

      // Once notified, process the queue
      while (!bufferQueue.empty()) {
        auto buffer = bufferQueue.front();
        bufferQueue.pop();
        ringBuffer->write(buffer);
      }

      // Release the lock
      lock.unlock();
    }
  }
  //============================================================================
private:
  std::unique_ptr<RingBuffer> ringBuffer;
  std::queue<juce::AudioBuffer<SampleType>> bufferQueue;
  std::condition_variable queueConditionVariable;
  std::mutex queueMutex;
};
} // namespace processor
} // namespace dsp
} // namespace dmt