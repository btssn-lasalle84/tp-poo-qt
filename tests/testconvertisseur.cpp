#include <QtWidgets>
#include <QtTest>
#include "ihmconvertisseur.h"

class TestConvertisseur : public QObject
{
    Q_OBJECT
  private:
    IHMConvertisseur* ihmConvertisseur;

  public:
    TestConvertisseur();
    ~TestConvertisseur();
  private slots:
    void testConvertir();
    void testConvertir_data(); // le suffixe *_data est obligatoire
};

TestConvertisseur::TestConvertisseur() : ihmConvertisseur(new IHMConvertisseur)
{
}

TestConvertisseur::~TestConvertisseur()
{
    delete ihmConvertisseur;
}

void TestConvertisseur::testConvertir()
{
    QFETCH(QString, valeur);
    QFETCH(QString, resultat);
    QFETCH(QString, unite);
    QLineEdit*   lineEdit        = ihmConvertisseur->valeurAConvertir;
    QLabel*      labelResultat   = ihmConvertisseur->resultatConversion;
    QLabel*      labelUnite      = ihmConvertisseur->uniteConversion;
    QPushButton* boutonConvertir = ihmConvertisseur->boutonConvertir;

    lineEdit->clear();
    QTest::keyClicks(lineEdit, valeur); // °C
    QTest::mouseClick(boutonConvertir, Qt::LeftButton);

    QCOMPARE(lineEdit->text(), valeur);
    QCOMPARE(labelResultat->text(), resultat);
    QCOMPARE(labelUnite->text(), unite);
}

void TestConvertisseur::testConvertir_data()
{
    QTest::addColumn<QString>("valeur");
    QTest::addColumn<QString>("resultat");
    QTest::addColumn<QString>("unite");

    QTest::newRow("none") << ""
                          << "--.--"
                          << " °F";
    QTest::newRow("int") << "10"
                         << "50.00"
                         << " °F";
    QTest::newRow("double") << "20.5"
                            << "68.90"
                            << " °F";
}

QTEST_MAIN(TestConvertisseur)
#include "testconvertisseur.moc"
