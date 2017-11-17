import java.util.*;
ConfigurationBuilder cb;
Date lastTweet;
TwitterStream twitterStream;
StatusListener listener;

String hashtag = "#lunafete";
color twitterColors[];
int twitterDuration[];
String saveText = "";

void initTwitter() {
  twitterColors = new color[10];
  twitterDuration = new int[10];
  
  //Credentials
  
  setupStreamListener();
}

void drawTwitter() {
  text(saveText, 100, 100);
  for (int i = 0; i < 10; i++) {
    if (twitterDuration[i] > 0) {
      twitterDuration[i]--;
      strip.setBalloon(i, twitterColors[i]);
    }
  }
}

void setTwitterColor(int ind, color c) {
  if (ind >= 0 && ind < 10) {
    twitterDuration[ind] = 2000;
    twitterColors[ind] = c;
  }
}


////////////////////////////////////////////////////////////////////////////
void setupStreamListener() {
  FilterQuery query = new FilterQuery(hashtag);
  twitterStream = new TwitterStreamFactory(cb.build()).getInstance();
  
  listener = new StatusListener() {
    @Override
      public void onStatus(Status status) {
      saveText = "@" + status.getUser().getScreenName() + " - " + status.getText();
      println("@" + status.getUser().getScreenName() + " - " + status.getText());
    }

    @Override
      public void onDeletionNotice(StatusDeletionNotice statusDeletionNotice) {
      println("Got a status deletion notice id:" + statusDeletionNotice.getStatusId());
    }

    @Override
      public void onTrackLimitationNotice(int numberOfLimitedStatuses) {
      println("Got track limitation notice:" + numberOfLimitedStatuses);
    }

    @Override
      public void onScrubGeo(long userId, long upToStatusId) {
      println("Got scrub_geo event userId:" + userId + " upToStatusId:" + upToStatusId);
    }

    @Override
      public void onStallWarning(StallWarning warning) {
      println("Got stall warning:" + warning);
    }

    @Override
      public void onException(Exception ex) {
      println("Couldn't connect: " + ex);
    }
  };
  twitterStream.addListener(listener);
  twitterStream.filter(query);
}