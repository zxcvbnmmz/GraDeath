#ifndef _MACRO_H__
#define _MACRO_H__

// 関数の使用を禁止するマクロ
// DEPRECATED void Func();
// のように書けば、Funcを呼んだ箇所でエラーが起きる
#define DEPRECATED __declspec(deprecated)

// インスタンスを作成しつつオブジェクトプールに追加する関数を作るマクロ
// Refを継承したクラスでのみ使用できる
// class T : public Ref{
//  CREATE(T);
// }
// のように、CREATEマクロに自身のクラス名を渡すことで、T::Createが作成される
#define CREATE(C)								\
static C* Create(){								\
	C* c = new C;								\
	if(c != nullptr){							\
		ObjectPoolManager::GetInstance()->		\
					GetCurrentPool()->Add(c);	\
		return c;								\
	}											\
	return nullptr;								\
}

// 作成に失敗したRefを継承するためのマクロ
// REF_CLASS(T){};
// の様に書けばRefを継承したクラスTが出来る
// CREATEマクロをこのマクロ一つで同時に追加したいが問題点有
#define REF_CLASS(CLASS) class CLASS : public Ref


// 試作マクロ
// REF_CLASS_EX(T)
//  ...
// REF_CLASS_END
// とすればRefを継承し、T::Createが追加されたクラスが作られる
// 最後のREF_CLASS_ENDのみっともなさをどうにかしたいが、CREATEマクロを同時に追加するには現状これが最適か
#define REF_CLASS_EX(CLASS) class CLASS : public Ref{	\
	CREATE(CLASS);		\

#define REF_CLASS_END };
 

#endif	// end of Macro