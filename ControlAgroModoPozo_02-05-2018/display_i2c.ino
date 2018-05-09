int display_init(){
  lcd.init();
  delay(40);
  lcd.backlight();
  delay(40);
  lcd.clear();
  return 0;
}

void print_welcome_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,0);
  lcd.print("IEH INGENIERIA SPA");
  lcd.setCursor(0,1);
  lcd.print("IZARO PRINCIPAL");
  lcd.setCursor(0,2);
  lcd.print("POZO 3");
}

void print_error_sd_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,0);
  lcd.print("ERROR:");
  lcd.setCursor(0,1);
  lcd.print("SD CARD NOT FOUND");
  lcd.setCursor(0,2);
  lcd.print("OR FILE IS CORRUPT");
}

void print_sd_card_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("SD CARD OK");
}

void print_error_load_config(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("ERROR:");
  lcd.setCursor(0,2);
  lcd.print("FILE IS CORRUPT!");
}

void print_load_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("LOAD CONFIG OK");
}

void print_config_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("SYSTEM");
  lcd.setCursor(0,2);
  lcd.print("CONFIGURATION");
}

void print_input_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("INPUT CONFIG OK");
}

void print_output_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("OUTPUT CONFIG OK");
}

void print_rtc_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("RTC CONFIG OK");
}

void print_rtc_config_fail_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("SERVER NOT FOUND");
  lcd.setCursor(0,2);
  lcd.print("RTC NO SYNC");
}

void print_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("CONFIGURATION OK");
}

void print_stay_for_3G_connection(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("STAY FOR 3G");
}

void print_rtc_config_init(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("RTC CONFIG");
}

void print_variables(){
  
}

void print_system_config_ok_msg(){
  delay(40);
  lcd.clear();
  delay(40);
  lcd.setCursor(0,1);
  lcd.print("SYSTEM CONFIG OK");
}
