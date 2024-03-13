
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
class OscilloscopeProcessor
{
  using RingBuffer = dmt::dsp::data::RingBuffer<SampleType>;

public:
  ~OscilloscopeProcessor()
  {
    kill = true;
    std::unique_lock<std::mutex> lock(closeMutex);
    killConditionVariable.wait(lock,
                               [this] { return this->closed.get() == true; });
    lock.unlock();
  }

  //============================================================================
  void prepareToPlay(double sampleRate, int /*samplesPerBlock*/)
  {
    ringBuffer = std::make_unique<RingBuffer>(2, sampleRate);
    transferThread =
      std::thread(&OscilloscopeProcessor::transferThreadCallback, this);
    transferThread.detach();
  }
  void processBlock(juce::AudioBuffer<SampleType>& buffer)
  {
    juce::AudioBuffer<SampleType> bufferCopy(buffer);
    bufferQueue.push(bufferCopy);
  }
  //============================================================================
  void transferThreadCallback()
  {
    while (kill.get() == false) {
      std::unique_lock<std::mutex> lock(queueMutex);

      // Wait until the queue is not empty
      queueConditionVariable.wait(
        lock, [this] { return !this->bufferQueue.empty(); });

      while (!bufferQueue.empty()) {
        auto buffer = bufferQueue.front();
        bufferQueue.pop();
        ringBuffer->write(buffer);
      }

      lock.unlock();
    }
    closed = true;
  }
  //============================================================================
private:
  std::unique_ptr<RingBuffer> ringBuffer;
  std::queue<juce::AudioBuffer<SampleType>> bufferQueue;
  std::condition_variable queueConditionVariable;
  std::condition_variable killConditionVariable;
  std::mutex queueMutex;
  std::mutex closeMutex;
  std::thread transferThread;
  juce::Atomic<bool> kill{ false };
  juce::Atomic<bool> closed{ true };
};
} // namespace processor
} // namespace dsp
} // namespace dmt