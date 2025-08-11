[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver MAG3110

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/mag3110/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

FreescaleのMAG3110は、小型で低消費電力のデジタル3軸磁力計です。3軸加速度計と併用することで、方位に依存しない電子コンパスを実現し、正確な方位情報を提供できます。標準のI2Cシリアルインターフェース出力とスマートな組み込み機能を備えています。MAG3110は、最大80Hzの出力データレート（ODR）で磁場を測定でき、これらの出力データレートは12msから数秒までのサンプル間隔に対応します。

LibDriver MAG3110は、LibDriverがリリースしたMAG3110のフル機能ドライバです。磁場読み取りなどの機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver MAG3110のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver MAG3110用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver MAG3110ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver MAG3110プログラミング例が含まれています。

/ docディレクトリには、LibDriver MAG3110オフラインドキュメントが含まれています。

/ datasheetディレクトリには、MAG3110データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/mag3110/index.html](https://www.libdriver.com/docs/mag3110/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。