#include "ResourseManager/ModelManager/ModelManager.h"
#include "Model/CwnSkinMesh.h"
#include "Model/CwnStaticMesh.h"

#define MAX_MODEL 10

namespace ModelManager{

namespace CWN{
namespace SKIN{
struct Data{
	CwnSkinMesh* mesh;
	const char* tag;
	Data* next;
	Data* prev;
	Data () :next ( nullptr ), prev ( nullptr ){}
};

namespace {
	Data first;
}

CwnSkinMesh* Get ( char* tag ){
	Data* data = first.next;

	while ( data != nullptr ){
		if ( !strcmp ( data->tag, tag ) ){
			return data->mesh;
		}
		data = data->next;
	}

	return nullptr;
}

bool Load ( char* fileName, char* path, const char* tag ){
	Data* data = &first;
	Data* next = data->next;
	if ( !strcmp ( tag, "" ) ){
		tag = fileName;
	}

	while ( next ){
		if ( !strcmp ( next->tag, tag ) ){
			return false;
		}
		next = next->next;
	}

	data = &first;
	next = data->next;
	while ( next != nullptr ){
		data = next;
		next = next->next;
	}

	next = new Data;
	next->mesh = new CwnSkinMesh;
	bool ret = next->mesh->LoadCwn ( fileName, path );
	if ( !ret ){
		delete next->mesh;
		delete next;
		return false;
	}

	next->tag = tag;
	data->next = next;
	next->prev = data;

	return true;
}

void Release (){
	Data* data = first.next;
	while ( data != nullptr ){
		Data* temp = data->next;

		delete data->mesh;
		delete data;
		data = nullptr;
		data = temp;
	}
}

bool Release ( const char* tag ){
	Data* data = first.next;
	while ( data != nullptr ){
		if ( !strcmp ( data->tag, tag ) ){
			Data* prev = data->prev;
			prev->next = data->next;
			if ( data->next ){
				// 次の前のデータのポインタに前のデータのポインタを渡しておく
				data->next->prev = prev;
			}

			delete data->mesh;
			delete data;
			data = nullptr;
			return true;
		}
		data = data->next;
	}
	return false;
}
};	// end of namespace SKIN


namespace STATIC{
struct Data{
	CwnStaticMesh* mesh;
	const char* tag;
	Data* next;
	Data* prev;
	Data () :next ( nullptr ), prev ( nullptr ){}
};

namespace {
	Data first;
}

CwnStaticMesh* Get ( char* tag ){
	Data* data = first.next;

	while ( data != nullptr ){
		if ( !strcmp ( data->tag, tag ) ){
			return data->mesh;
		}
		data = data->next;
	}

	return nullptr;
}

bool Load ( char* fileName, char* path, const char* tag ){
	Data* data = &first;
	Data* next = data->next;
	if ( !strcmp ( tag, "" ) ){
		tag = fileName;
	}

	while ( next ){
		if ( !strcmp ( next->tag, tag ) ){
			return false;
		}
		next = next->next;
	}

	data = &first;
	next = data->next;
	while ( next != nullptr ){
		data = next;
		next = next->next;
	}

	next = new Data;
	next->mesh = new CwnStaticMesh;
	bool ret = next->mesh->LoadCwn ( fileName, path );
	if ( !ret ){
		delete next->mesh;
		delete next;
		return false;
	}

	next->tag = tag;
	data->next = next;
	next->prev = data;

	return true;
}

void Release (){
	Data* data = first.next;
	while ( data != nullptr ){
		Data* temp = data->next;

		delete data->mesh;
		delete data;
		data = nullptr;
		data = temp;
	}
}

bool Release ( const char* tag ){
	Data* data = first.next;
	while ( data != nullptr ){
		if ( !strcmp ( data->tag, tag ) ){
			Data* prev = data->prev;
			prev->next = data->next;
			if ( data->next ){
				// 次の前のデータのポインタに前のデータのポインタを渡しておく
				data->next->prev = prev;
			}

			delete data->mesh;
			delete data;
			data = nullptr;
			return true;
		}
		data = data->next;
	}
	return false;
}
};	// end of namespace STATIC
};	// end of namespace CWN
};