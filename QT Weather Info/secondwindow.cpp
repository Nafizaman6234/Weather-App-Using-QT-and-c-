#include "secondwindow.h"
#include "ui_secondwindow.h"
#include "qjsonarray.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
}
QString get_name;
SecondWindow::~SecondWindow()
{
    delete ui;
}


void SecondWindow::on_pushButton_clicked()
{

    get_name = ui->lineEdit->text();
    ui->label_3->setText("Name:"+get_name);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Construct the URL for the weather API request
    QString apiKey = "Your openweathermap api key here......................................................."; // Replace with your API key
    QString apiUrl = "https://api.openweathermap.org/data/2.5/weather?q=" + get_name + "&appid=" + apiKey;

    // Create a QNetworkRequest with the API URL
    QNetworkRequest request((QUrl(apiUrl)));

    // Send the GET request
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, this, &SecondWindow::handleWeatherResponse);
    ui->lineEdit->clear();
}

void SecondWindow::handleWeatherResponse()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();

        // Parse the JSON data
        QJsonDocument jsonResponse = QJsonDocument::fromJson(data);
        QJsonObject jsonObject = jsonResponse.object();

        // Extract and display weather information
        QString name = jsonObject["name"].toString();
        double temperature = jsonObject["main"].toObject()["temp"].toDouble() - 273.15; // Convert from Kelvin to Celsius
        int humidity = jsonObject["main"].toObject()["humidity"].toInt();
        QString conditions = jsonObject["weather"].toArray()[0].toObject()["description"].toString();
        double feels_like = jsonObject["main"].toObject()["feels_like"].toDouble() -273.15;
        double pressure = jsonObject["main"].toObject()["pressure"].toDouble();
        QString country = jsonObject["sys"].toObject()["country"].toString();

        ui->label_3->setText("Name: " + name);
        ui->label_7->setText("Country: " + country);
        ui->label_4->setText("Temperature: " +QString::number(temperature) + "°C");
        ui->label_6->setText("Feels_like: " +QString::number(feels_like) + "°C");
        ui->label_8->setText("Pressure: " +QString::number(pressure) + " hpa");
        ui->label_9->setText("Humidity: " + QString::number(humidity) + "%");
        ui->label_5->setText("Weather: " + conditions);
    } else {
        // Handle API request errors
        ui->label_5->setText("Error: " + reply->errorString());
    }

    // Clean up
    reply->deleteLater();
}

