#ifndef TRANS_TRAIN_H
#define TRANS_TRAIN_H

#define TRAINSPLIT_FMT "https://timetables.trainsplit.com/times.aspx?uid=%s&date=%.4s%.2s%.2s"
#define TRAINSPLIT_FMT_ARG(ID, ISO) ID, ISO, &(ISO)[5], &(ISO)[8]

#define RTT_FMT "https://www.realtimetrains.co.uk/service/gb-nr:%s/%s/detailed"
#define RTT_FMT_ARG(ID, ISO) ID, ISO

struct trans_train {
  char id[7];
};

#define train(ID, FROM, TO) { \
  .type = TRANS_TRAIN, \
  .from = FROM, \
  .to = TO, \
  .as.train.id = ID \
}

#endif /* TRANS_TRAIN_H */
