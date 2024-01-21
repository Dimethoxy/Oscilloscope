//==============================================================================
#pragma once
//==============================================================================
#include <JuceHeader.h>
//==============================================================================
/**
    @class RingBuffer
    @brief A template class that represents a ring buffer for audio data.

    The RingBuffer class provides a circular buffer implementation for storing
    audio data. It supports reading and writing audio data to and from the
    buffer.

    @tparam SampleType The type of audio data stored in the buffer.
*/
template<typename SampleType>
class RingBuffer
{
public:
  //============================================================================
  /**
      Constructs a RingBuffer object with the specified number of channels an
      samples.

      @param numChannelsToAllocate The number of channels to allocate in the
      buffer.
      @param numSamplesToAllocate The number of samples to allocate in the
      buffer.
  */
  RingBuffer(const int numChannelsToAllocate, const int numSamplesToAllocate)
    : bufferSize(numSamplesToAllocate)
    , numChannels(numChannelsToAllocate)
    , position(0)
    , buffer(std::make_unique<AudioBuffer<SampleType>>(numChannelsToAllocate,
                                                       numSamplesToAllocate))
  {
  }
  //============================================================================
  /**
      An enum class representing the result of an operation.

      The OperationResult enum class represents the result of an operation.
      It is used to indicate whether an operation was successful or not.

      @see read
      @see write
  */
  enum class OperationResult
  {
    Success,           /**< The operation was successful. */
    ErrorSizeMismatch, /**< The operation failed due to a size mismatch. */
  };
  //============================================================================
  /**
      Reads audio data from the buffer into the target buffer.

      @param targetBuffer The buffer to copy the audio data into.
  */
  const OperationResult read(
    AudioBuffer<SampleType>& targetBuffer) const noexcept
  {
    // If targetBuffer is smaller than the RingBuffer we need to return early
    if (targetBuffer.getNumChannels() < numChannels ||
        targetBuffer.getNumSamples() < bufferSize) {
      jassertfalse; // Juce does not support exceptions, so we assert instead
      return OperationResult::ErrorSizeMismatch;
    }
    // We need to lock the buffer for reading to ensure thread safety
    lock.enterRead();
    // Caching the atomic should be cheaper than calling get() every iteration
    const int startingPosition = position.get();
    // Iterate the samples first to improve thread safety
    for (int sample = 0; sample < bufferSize; ++sample) {
      // We use modulo to wrap the index around the buffer
      const int ringPosition = (startingPosition + sample) % bufferSize;
      // Iterate the channels second to improve thread safety
      for (int channel = 0; channel < numChannels; ++channel) {
        // Copy the sample from the buffer to targetBuffer
        targetBuffer.copyFrom(
          channel, sample, *buffer, channel, ringPosition, 1);
      }
    }
    // We need to unlock the buffer after reading to ensure thread safety
    lock.exitRead();
    // We return the result of the operation
    return OperationResult::Success;
  }
  //============================================================================
  /**
      Writes audio data from the bufferToWrite into the buffer.

      @param bufferToWrite The buffer containing the audio data to write.
  */
  const OperationResult write(
    const AudioBuffer<SampleType>& bufferToWrite) noexcept
  {
    // If bufferToWrite is larger than the RingBuffer we need to return early
    if (bufferToWrite.getNumChannels() > numChannels ||
        bufferToWrite.getNumSamples() > bufferSize) {
      jassertfalse; // Juce does not support exceptions, so we assert instead
      return OperationResult::ErrorSizeMismatch;
    }
    // We need to lock the buffer for writing to ensure thread safety
    lock.enterWrite();
    // Caching the atomic should be cheaper than calling get() every iteration
    const int startingPosition = position.get();
    // Iterate the samples first to improve thread safety
    for (int sample = 0; sample < bufferSize; ++sample) {
      // We use modulo to wrap the index around the buffer
      const int ringPosition = (startingPosition + sample) % bufferSize;
      // Iterate the channels second to improve thread safety
      for (int channel = 0; channel < numChannels; ++channel) {
        // Copy the sample from bufferToWrite to the buffer
        buffer->copyFrom(
          channel, ringPosition, bufferToWrite, channel, sample, 1);
      }
    }
    // We update the position for the readers after we've written the buffer
    position.set((startingPosition + bufferSize) % bufferSize);
    // We need to unlock the buffer after writing to ensure thread safety
    lock.exitWrite();
    // We return the result of the operation
    return OperationResult::Success;
  }
  //============================================================================
private:
  const int bufferSize;                            // Number of samples
  const int numChannels;                           // Number of channels
  juce::Atomic<int> position;                      // Current starting position
  std::unique_ptr<AudioBuffer<SampleType>> buffer; // Buffer to store audio data
  juce::ReadWriteLock lock;                        // Lock for thread safety
};
