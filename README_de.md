[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAG3110
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mag3110/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der MAG3110 von Freescale ist ein kleines, stromsparendes, digitales 3-Achsen-Magnetometer. Das Gerät kann in Verbindung mit einem 3-Achsen-Beschleunigungssensor verwendet werden, um einen richtungsunabhängigen elektronischen Kompass zu realisieren, der genaue Kursinformationen liefert. Er verfügt über eine standardmäßige serielle I2C-Schnittstelle und intelligente eingebettete Funktionen. Der MAG3110 misst Magnetfelder mit einer Ausgangsdatenrate (ODR) von bis zu 80 Hz; diese Ausgangsdatenraten entsprechen Abtastintervallen von 12 ms bis zu mehreren Sekunden.

LibDriver MAG3110 ist ein voll funktionsfähiger Treiber für MAG3110, der von LibDriver eingeführt wurde. Er bietet Magnetfeldmessung und weitere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver MAG3110-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver MAG3110 IIC.

/test enthält den Testcode des LibDriver MAG3110-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver MAG3110-Beispielcode.

/doc enthält das LibDriver MAG3110-Offlinedokument.

/Datenblatt enthält MAG3110-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_mag3110_basic.h"

uint8_t res;
uint32_t i;
float ut[3];

/* basic init */
res = mag3110_basic_init();
if (res != 0)
{
    return 1;
}

...

/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    mag3110_interface_delay_ms(1000);

    /* read data */
    res = mag3110_basic_read((float *)ut);
    if (res != 0)
    {
        (void)mag3110_basic_deinit();

        return 1;
    }

    /* output */
    mag3110_interface_debug_print("%d/%d\n", (uint32_t)(i + 1), (uint32_t)3);
    mag3110_interface_debug_print("x is %0.3fuT.\n", ut[0]);
    mag3110_interface_debug_print("y is %0.3fuT.\n", ut[1]);
    mag3110_interface_debug_print("z is %0.3fuT.\n", ut[2]);
    
    ...
}

...
    
/* deinit */
(void)mag3110_basic_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/mag3110/index.html](https://www.libdriver.com/docs/mag3110/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.