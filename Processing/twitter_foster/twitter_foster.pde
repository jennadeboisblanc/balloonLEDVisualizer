
import processing.serial.*;
import cc.arduino.*;
import org.firmata.*;
//processing.data.JSONArray colors;

Arduino arduino;
import java.util.*;
ConfigurationBuilder cb;
Date lastTweet;
long lastChecked = 0;

boolean debugging = false;

TwitterStream twitterStream;
StatusListener listener;

Serial myPort;

String hashtag = "#MisterBB";
String saveText = "";
String saveText1 = "";
String saveText2 = "";
int val = 0;
float red = 0;
float green = 0;
float blue = 0;

//processing.data.JSONObject colObj;

void setup() {
  size(550, 550);
  background(0);
  smooth();
  
  //colors = loadJSONArray("colors.json");
  //colObj = colors.getJSONObject(0);

  cb = new ConfigurationBuilder();
  cb.setOAuthConsumerKey("4bzdsxURiqbluY2EGqE3PbD2b");
  cb.setOAuthConsumerSecret("BA1xaelLXX47m3vOdiUBYsHCSJGiFabyDHq84gbaZyKdKgBzRK");
  cb.setOAuthAccessToken("567399817-QIyM8fyLFuYbkHsRi3RqyrYbnO6llSH7Fev3bLvZ");
  cb.setOAuthAccessTokenSecret("C0iBx6BmMKRbp2abRcBVA5l2FdMqPzATFOUnqh1o0vdf2");
  setupStreamListener();
  if (debugging) println(Arduino.list());
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(9, Arduino.OUTPUT);
  arduino.pinMode(10, Arduino.OUTPUT);
  arduino.pinMode(11, Arduino.OUTPUT);
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  //saveText1 = "7";
  //saveText2 = "palegoldenrod";
  delay(100);
  
  //String hex = colObj.getString(saveText2);
  //println(hex);
  //hex = hex.substring(1);
  //int fullColor = unhex(hex);
  //red = red(fullColor);
  //green = green(fullColor);
  //blue = blue(fullColor);
  println(saveText);
  if (saveText.indexOf("10") != -1) {
    val = 10;
  }
  for (int i = 0; i < 10; i++) {
    if (saveText.indexOf(str(i)) != -1) {
      val = i;
    }
  }
  //println(saveText2.indexOf("blue"));
  //println(saveText2);
  saveText = saveText.toLowerCase();
  //myPort.write(int(saveText1));
  //myPort.write(str(red));
  //myPort.write(str(green));
  //myPort.write(str(blue));
  if (saveText.indexOf("blue") != -1) {
    myPort.write(val);
    myPort.write(0);
    myPort.write(0);
    myPort.write(255);
  }
  if (saveText.indexOf("green") != -1) {
    myPort.write(val);
    myPort.write(0);
    myPort.write(255);
    myPort.write(0);
  }
  if (saveText.indexOf("red") != -1) {
    myPort.write(val);
    myPort.write(255);
    myPort.write(0);
    myPort.write(0);
  }
  if (saveText.indexOf("yellow") != -1) {
    myPort.write(val);
    myPort.write(255);
    myPort.write(255);
    myPort.write(0);
  }
  if (saveText.indexOf("orange") != -1) {
    myPort.write(val);
    myPort.write(255);
    myPort.write(100);
    myPort.write(0);
  }
  if (saveText.indexOf("purple") != -1) {
    myPort.write(val);
    myPort.write(255);
    myPort.write(0);
    myPort.write(255);
  }
  if (saveText.indexOf("white") != -1) {
    myPort.write(val);
    myPort.write(255);
    myPort.write(255);
    myPort.write(255);
  }
  if (saveText.indexOf("black") != -1) {
    myPort.write(val);
    myPort.write(0);
    myPort.write(0);
    myPort.write(0);
  }
  if (saveText.indexOf("off") != -1) {
    myPort.write(val);
    myPort.write(0);
    myPort.write(0);
    myPort.write(0);
  }
}

void setupStreamListener() {
  FilterQuery query = new FilterQuery(hashtag);
  twitterStream = new TwitterStreamFactory(cb.build()).getInstance();

  listener = new StatusListener() {
    @Override
      public void onStatus(Status status) {
      saveText = status.getText();
      int hashtag = saveText.indexOf("#");
      saveText1 = saveText.substring(0, 1);
      saveText2 = saveText.substring(2, hashtag);
      if (debugging) {
        println(saveText1);
        println("@" + status.getUser().getScreenName() + " - " + status.getText());
      }
    }

    @Override
      public void onDeletionNotice(StatusDeletionNotice statusDeletionNotice) {
      if (debugging) println("Got a status deletion notice id:" + statusDeletionNotice.getStatusId());
    }

    @Override
      public void onTrackLimitationNotice(int numberOfLimitedStatuses) {
      if (debugging) println("Got track limitation notice:" + numberOfLimitedStatuses);
    }

    @Override
      public void onScrubGeo(long userId, long upToStatusId) {
      if (debugging) println("Got scrub_geo event userId:" + userId + " upToStatusId:" + upToStatusId);
    }

    @Override
      public void onStallWarning(StallWarning warning) {
      if (debugging) println("Got stall warning:" + warning);
    }

    @Override
      public void onException(Exception ex) {
      if (debugging) println("Couldn't connect: " + ex);
    }
  };
  twitterStream.addListener(listener);
  twitterStream.filter(query);
}