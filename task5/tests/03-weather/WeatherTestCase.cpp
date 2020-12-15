//
// Created by Pavel Akhtyamov on 02.05.2020.
//

#include "WeatherTestCase.h"
#include "WeatherMock.h"

#include "cpr/cpr.h"

using ::testing::Return;

TEST(WeatherTest, NotExistingCity) {
  WeatherMock weather;
  cpr::Response response;

  // Configuring fake response:
  response.status_code = 404;

  EXPECT_CALL(weather, Get)
    .Times(1)
    .WillOnce(Return(response));
  ASSERT_THROW(weather.GetTemperature("NotExistingCity"), std::invalid_argument);

  weather.SetApiKey("SomeKey");
}

TEST(WeatherTest, ExistingCityTemperature) {
  WeatherMock weather;
  cpr::Response response;

  // Configuring fake response:
  response.status_code = 200;
  response.text = "{\"list\": [{\"main\": {\"temp\" : 6.9}}]}";

  EXPECT_CALL(weather, Get)
    .Times(1)
    .WillOnce(Return(response));
  EXPECT_EQ(weather.GetTemperature("Nightcity"), float(6.9));
}

TEST(WeatherTest, FirstCityWarmer) {
  WeatherMock weather;
  cpr::Response response1;
  cpr::Response response2;

  // Configuring fake response:
  response1.status_code = 200;
  response1.text = "{\"list\": [{\"main\": {\"temp\" : 41.0}}]}";
  response2.status_code = 200;
  response2.text = "{\"list\": [{\"main\": {\"temp\" : 36.7}}]}";

  EXPECT_CALL(weather, Get)
    .Times(2)
    .WillOnce(Return(response1))
    .WillOnce(Return(response2));
  EXPECT_EQ(weather.GetDifferenceString("Kairo", "Istambul"), "Weather in Kairo is warmer than in Istambul by 4 degrees");
}

TEST(WeatherTest, FirstCityColder) {
  WeatherMock weather;
  cpr::Response response1;
  cpr::Response response2;

  // Configuring fake response:
  response1.status_code = 200;
  response1.text = "{\"list\": [{\"main\": {\"temp\" : 36.7}}]}";
  response2.status_code = 200;
  response2.text = "{\"list\": [{\"main\": {\"temp\" : 41.0}}]}";

  EXPECT_CALL(weather, Get)
    .Times(2)
    .WillOnce(Return(response1))
    .WillOnce(Return(response2));
  EXPECT_EQ(weather.GetDifferenceString("Kairo", "Istambul"), "Weather in Kairo is colder than in Istambul by 4 degrees");
}
