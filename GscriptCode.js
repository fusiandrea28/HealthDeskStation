var ss = SpreadsheetApp.openById('your spreadsheet ID here');
var historyWeatherSheet = SpreadsheetApp.getActive().getSheetByName('Taipei City');
var logSheet = ss.getSheetByName('Log');
var taipeiToday = ss.getSheetByName('Sheet2');
var nextRow = logSheet.getLastRow() + 1;

var currentTimeDate10 = logSheet.getRange(3, 9).getDisplayValue();
var currentTimeDate20 = logSheet.getRange(3, 11).getDisplayValue();
var currentTimeDate30 = logSheet.getRange(3, 13).getDisplayValue();
var currentTimeDate40 = logSheet.getRange(3, 15).getDisplayValue();
var todayTime = logSheet.getRange(2, 3).getDisplayValue();

function doGet(e){
  //----------------------------------------------------------------------------------
  //write_google_sheet() function in esp32 sketch, is send data to this code block
  //----------------------------------------------------------------------------------
  //get data from ESP32
  if (e.parameter == 'undefined') {
    return ContentService.createTextOutput("Received data is undefined");
  }
  //----------------------------------------------------------------------------------
  ssid    = e.parameters.ssid;
  time    = e.parameters.time;
  date    = e.parameters.date;  
  temp    = e.parameters.temp;
  humid   = e.parameters.humid;
  co2       = e.parameters.co2;

  //----------------------------------------------------------------------------------
  logSheet.getRange("A" + nextRow).setValue(ssid);
  logSheet.getRange("B" + nextRow).setValue(date);
  logSheet.getRange("C" + nextRow).setValue(time);  
  logSheet.getRange("D" + nextRow).setValue(temp);
  logSheet.getRange("E" + nextRow).setValue(humid);
  logSheet.getRange("F" + nextRow).setValue(co2);
  //----------------------------------------------------------------------------------

  
  copyTodayWeather();

  findinWeatherHistory();

    //returns response back to ESP32
  return ContentService.createTextOutput("Status Updated in Google Sheet");
}

// get all the ID values we have in the sheet we want to check them. flat will convert all the returning
// 2D array of values in a 1D array with all the IDs
var idRange = historyWeatherSheet.getDataRange().getValues();

function findinWeatherHistory() {
  
  // Get the new incoming data (ID and Ok/Nok) with each form submit by accessing  
  // the trigger object e which is the submited and new form response row
  
  // Iterate for 10 years ago
  Logger.log("Looking for hystorical weather value...");

  for(i=0;i<idRange.length;i++){
    
    if(idRange[i][0] == currentTimeDate10){
      Logger.log("Found a match 10ys!");
      // set its value to the one submitted by the form
	    tempValueTemp10 = historyWeatherSheet.getRange(i+1, 2).getValue();
      logSheet.getRange(nextRow, 9).setValue(tempValueTemp10);

      tempValueHumid10 = historyWeatherSheet.getRange(i+1, 3).getValue();
      logSheet.getRange(nextRow, 10).setValue(tempValueHumid10);
    }
	
	  if(idRange[i][0] == currentTimeDate20){
      Logger.log("Found a match 20ys!");
      // set its value to the one submitted by the form
	    tempValueTemp20 = historyWeatherSheet.getRange(i+1, 2).getValue();
      logSheet.getRange(nextRow, 11).setValue(tempValueTemp20);

      tempValueHumid20 = historyWeatherSheet.getRange(i+1, 3).getValue();
      logSheet.getRange(nextRow, 12).setValue(tempValueHumid20);
    }
	
	  if(idRange[i][0] == currentTimeDate30){
      Logger.log("Found a match 30ys!");
      // set its value to the one submitted by the form
	    tempValueTemp30 = historyWeatherSheet.getRange(i+1, 2).getValue();
      logSheet.getRange(nextRow, 13).setValue(tempValueTemp30);

      tempValueHumid30 = historyWeatherSheet.getRange(i+1, 3).getValue();
      logSheet.getRange(nextRow, 14).setValue(tempValueHumid30);
    }
	
	  if(idRange[i][0] == currentTimeDate40){
      Logger.log("Found a match 40ys!");
      // set its value to the one submitted by the form
	    tempValueTemp40 = historyWeatherSheet.getRange(i+1, 2).getValue();
      logSheet.getRange(nextRow, 15).setValue(tempValueTemp40);

      tempValueHumid40 = historyWeatherSheet.getRange(i+1, 3).getValue();
      logSheet.getRange(nextRow, 16).setValue(tempValueHumid40);
    }

  }

}

function copyTodayWeather() {
  
  Logger.log("Value to look for: " + todayTime)

  
  // get all the ID values we have in the sheet we want to check them. flat will convert all the returning
  // 2D array of values in a 1D array with all the IDs
  var idRange2 = taipeiToday.getDataRange().getDisplayValues();
  
  Logger.log("Looking for today weather value...");

  for(i=0;i<idRange2.length;i++){

    if(idRange2[i][24] == todayTime){
      Logger.log("Found a match!");
      // set its value to the one submitted by the form
	    tempValueTemp = taipeiToday.getRange(i+1, 5).getValue();
      logSheet.getRange(nextRow, 7).setValue(tempValueTemp);

      tempValueHumid = taipeiToday.getRange(i+1, 12).getValue();
      logSheet.getRange(nextRow, 8).setValue(tempValueHumid);
    }
  }

}
