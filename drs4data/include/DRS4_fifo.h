/*
 * DRS4_fifo.h
 *
 *  Created on: Apr 6, 2017
 *      Author: S. Lukic
 */

#ifndef DRS4DATA_INCLUDE_DRS4_FIFO_H_
#define DRS4DATA_INCLUDE_DRS4_FIFO_H_

#include "DRS4_data.h"
#include <queue>
#include <vector>
#include <iostream>


namespace DRS4_data {

  struct Waveforms {
    Waveforms() : waveforms(NULL)
    {
      waveforms = new (std::nothrow) unsigned char [kNumberOfChipsMax * kNumberOfChannelsMax * 2 * kNumberOfBins];
    }
/*    Waveforms::Waveforms(unsigned nChips=1, unsigned nChannels=8) :
      waveforms(new (std::nothrow) unsigned char [nChips * nChannels * 2 * kNumberOfBins])
    { }*/
    ~Waveforms() {
      delete [] waveforms;
    }
    unsigned char *waveforms;
  } ;


  struct RawEvent {
    ~RawEvent();
    std::vector<Waveforms*> eventWaves;
    EHEADER header;
  };


  class DRS4_fifo {

  public:
    DRS4_fifo();
    ~DRS4_fifo();

    // Returns the time of the last event in ms since the beginning of the run.
    unsigned timeLastEvent() const ;
    // Returns the pointer to RawEvent object. The pointer is popped from the queue.
    // The caller is responsible for freeing the memory (deleting the pointer).
    // If the queue is empty, returns null pointer.
    RawEvent* read() ;
    // Push the pointer. The caller should have already reserved the memory.
    int write(RawEvent*) ;
    bool isEmpty() const { return eventQueue.empty(); }
    unsigned size() const {return eventQueue.size(); }

    void SetTimeBeginRun(unsigned tf) { msBeginRun = tf; };

    void Discard();

    static const unsigned maxSize = 10000;

  private:
    std::queue<RawEvent*> eventQueue;
    unsigned msLastEvent;
    unsigned msBeginRun;

  };

} // namespace DRS4_data

#endif /* DRS4DATA_INCLUDE_DRS4_FIFO_H_ */
