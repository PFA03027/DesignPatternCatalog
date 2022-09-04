# Design Pattern Implementation Catalog
 This is Design Pattern Implementation Catalog and my understanding and opinion for use
 
## Classification: Creation
### Abstract Factory
* C++ での実装: CreationPattern01_AbstractFactory/cpp_src
* Rust での実装: CreationPattern01_AbstractFactory/rust_src

これらの実装は、Abstract Factoryの典型的なサンプル構成を実装したものになる。

このパターンを実コードで適用し、再利用性のあるコードとして活用するには、

* 具象クラスの実装コードのビルド方法
* 具象クラスのインスタン生成方法
* 具象クラスのインスタンスへアクセス方法

に対する設計がさらに必要となる。
具象クラスの実装が、実装するコード内で完結している場合はこの点はあまり気にする必要がない。必要であったとしても、実装作業の手の内にあるので、どうにでもなる。

問題は、具象クラスが依存するシステムがビルドシステム内に存在しない場合である。

さらに、Abstract Factoryパターンを適用する動機から考えると、具象クラスの実装は他のシステムに依存する場合がほとんどであり、具象クラスが依存するシステムがビルドシステム内に存在しないことは普通に起きることと思われる。

例えば、システムコールを使用するオブジェクトに対しAbstract Factoryを適用する場合、Windows用とLinux用、Mac用それぞれのオブジェクトは、それぞれのシステムでしかビルドできない。

#### 具象クラスの実装コードのビルド方法
よって、具象クラスの実装コードのビルド方法に対しては、下記の実装が必要となる。

* 実装として、Abstract Factoryパターンを適用する。
* さらに具象クラスは、それぞれのビルドシステム(例えばMakefileで切り替える等)でのみビルドされるようにする。

#### 具象クラスのインスタン生成方法
同様に、(Abstract Productクラスではなく)Abstract Factoryクラスの具象クラスのインスタンを生成するコードも
具象クラスの定義を参照するため、ビルド方法と同様に下記の対応が必要になる。

* 具象クラスのインスタンを生成するコードは、それぞれのビルドシステム(例えばMakefileで切り替える等)でのみビルドされるようにする。

#### 具象クラスのインスタンスへアクセス方法
上記までで、ようやくAbstract Factoryの具象クラスのインスタンスオブジェクトが生成できた。
このAbstract Factoryの具象クラスをAbstract Factoryの抽象クラスへの参照に変換すると、
ようやくAbstract Factoryパターンにおけるクライアントコードがアクセス可能となる。
よって、

* Abstract Factoryの具象クラスのインスタンへの参照を、Abstract Factoryの抽象クラスへの参照に変換する実装までを、それぞれのビルドシステム(例えばMakefileで切り替える等)でのみビルドされるようにする。

とする必要がある。
ここまで実装とビルドシステムで考慮することで、ようやくAbstract Factoryパターンの実用的に使用することができる。

意外と、、、重たいですね。
感覚的には、同時期に複数プラットフォームをサポートしたり、ある程度長い期間（３～４年、あるいはそれ以上）コードを流用して継続的に成長させるソフトの場合は、最初から考慮に入れていても価値があると感じます。
いかがでしょうか？　でも意外とそういったソフト、ありませんか？

CreationPattern01_AbstractFactory_Practical は、CreationPattern01_AbstractFactoryに対し、straw_housemaker、wood_housemaker、stone_housemakerがそれぞれ異なるシステムに依存する場合を想定して、仕立て直したものです。

主な変更点は、以下です。

* abstract_house_productの具象クラスの生成I/Fを追加し、クライアントコードからは隠蔽
* 再利用対象となるクライアントコードと、Abstract Factoryの具象クラスの実装コードを意図がわかりやすいように別フォルダに分離。

#### 抽象化の粒度
Windowシステムが用意する部品レベル（ボタンやリストボックス等）でAbstract FactoryパターンのAbstract Productを定義するサンプルを見かけます。
実際にこのレベルで抽象したソフト運用するのは困難ではないかと感じます。
対象とするシステムに対する細かな違いを把握し、互換性がない違いを吸収するのが大変になるからです。
このような場合、品質を維持するために、優秀な人材を確保するだけなく、確保した人材を長期間、同一のソフトに対して充てる必要があります。
しかしながら、優秀な人材はそうたくさんいません。こうなってしまうと担当を入れ替えるのが難しく、担当した人も新しいことに挑戦する機会がなくなり不幸です。
折角の再利用性を高めるためのデザインパターンの適用も、重いばかりです。
結果として負のメンテナンススパイラルに陥ってしまいます。

では、どれぐらいの粒度が良いでしょうか？

これは、個人的な見解ですが、MVCモデルの、V単位ぐらいの大きな粒度でAbstract Productの具象クラスを定義しても良いぐらいではないかと思います（もちろんその中間ぐらいでもよい）。
このぐらいのレベルだと具象クラス内の実装の自由度が高く、具象クラスが対象とするシステムに集中して開発できます。
もちろん、Abstract Factoryパターンで、複数のシステムをサポートしているという設計の理解は必要です。
とはいえ、依存するシステムの入れ替わりとともに人を入れ替えることも可能になるのではないでしょうか。



## Classification: Creation
### Factory Method
* C++ での実装: CreationPattern03_FactoryMethod/cpp_src
* C++ での実装(ラムダ式方式): CreationPattern03_FactoryMethod/cpp_src2
* Rust での実装: CreationPattern03_FactoryMethod/rust_src

これらの実装は、Factory Methodパターンのサンプル実装です。

CreationPattern03_FactoryMethod/cpp_srcは、デザインパターン本でもともと紹介されていた構成をそのまま実装適用したコードです。

一方で、CreationPattern03_FactoryMethod/cpp_src2やCreationPattern03_FactoryMethod/rust_srcは、ラムダ式やクロージャを使用した実装コードです。
こちらの場合、デザインパターン本の実装方式で課題になりやすい、Creatorのサブクラス化が不要になります。
ラムダ式やクロージャの場合、サブクラス化で実現している具象クラスが保持するメンバ変数やデータをキャプチャによって補っている形ですね。
こちらの実装の方が現代的と思われます。

#### クロージャの型について
https://qiita.com/terakoya76/items/f9e2b0bda491aff19b6f

## Classification: Structure
### Adapter
* C++ での実装(コンポジットタイプ): StructurePattern01_Adapter\cpp_src
* C++ での実装(多重継承タイプ): StructurePattern01_Adapter\cpp_src2
* Rust での実装: StructurePattern01_Adapter\rust_src

これらの実装は、Apdaterパターンのサンプル実装で、I/Fを適合させる目的でAdapterパターンを使用したサンプルです。

C++での実装では、コンポジットタイプの実装の形は定石で、Adapteeクラスへのポインタを保持します。
一方で、Rustの実装では、トレイトを追加実装する形としました。これは、C++では多重継承タイプに相当する実装方式と考えられます。

Adapterパターンの大事なポイントは、既存のクラスには手を加えることなく、I/Fを揃えることが出来る点ですね。

### 補足
もしAdapteeクラスがFactory系の場合は、実質的にFactory Methodパターンになります。この場合、生成されるオブジェクトにもAdapterを適用する必要があるでしょう。


## Classification: Structure
### Composite
* C++ での実装(共通的操作を仮想メンバ関数による実装例): StructurePattern03_Composite\cpp_src
* C++ での実装(共通的操作をVisitorパターンで実装した例): StructurePattern03_Composite\cpp_src2
* C++ での実装(共通的操作をVisitorパターンとdynamic_castで実装した例): StructurePattern03_Composite\cpp_src3
* Rust での実装: StructurePattern03_Composite\rust_src

みんな大好き、木構造のCompositeパターンです。

Compositeパターンの悩ましい点は、具象化クラスの個別I/Fに対する共通化の是非ですね。どうしてもトレードオフが発生するところです。
サンプルコードでは、ベースとなるクラスで派生クラスの個別I/Fの実装を行わずにComposite構造をスキャンできるように、
Visitorパターンを使ったサンプルとしました。

StructurePattern03_Composite\cpp_src3は、ベースクラスから派生クラスの詳細を分離する
ような場合（フレームワークや何らかのライブラリの実装等）に適用できる方法の一つと思います。
