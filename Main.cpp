#include "Window.hpp"

#include <gl3w.h>
#include <glfw3.h>

// Containers
// EntityEngine
// Renderer
// Utilities or Essentials

// TODO: cmake --build in ./Builds
// TODO: target_include_directories(...);
// TODO: target_link_libraries(...);
// TODO: ./Build.bat
// TODO: ./Build.bat --profile
// TODO: ./Build.bat --debug
// TODO: ./Build.bat --release
// TODO: ./Build.bat --cbench

// TODO: ./Run.bat --profile
// TODO: ./Run.bat --cbench --debug

// typy obiektowe;
// typy obiektowe oraz referencyjne;
// typy referencyjne;

struct Vector;
struct obVector;
struct refVector;
void Create_Vector(Buffer* const ob); // Create;
void Destroy_Vector(Buffer* const ob); // Destroy;
void Allocate_Vector(Buffer** const ob); // Allocate + Create;
void Deallocate_Vector(Buffer** const ob); // Deallocate + Destroy;

#define VECTOR(Function) Function
#define ALLOCA(Function) Function
class Vector3F
{
	public:
	float X, Y, Z;
	private:

};
class Vector
{
	public:
	DEFAULT_5_RULE();
	void Create()
	{
		this->m_X = 0;
		this->m_Y = 0;
		this->m_Z = 0;

	}
	void Destroy()
	{
		
	}
	void Allocate(Vector** ob)
	{
		Main::Allocate(ob);
		ob->Create();

	}
	void Deallocate(Vector** ob)
	{
		ob->Destroy();
		Main::Deallocate(ob);

	}

	private:
	uint32_t m_X, m_Y, m_Z;

};



int32_t main()
{
	// IMPORTANT: Responsability Rule!
	// IMPORTANT: Error Rule!
	// IMPORTANT: Vector vs Vector3F
	// IMPORTANT: Lstack vs Lheap
	
	Vector* vec;
	VECTOR(AllocateCreate(&vec, 0.0F, 0.0F, 0.0F));
	VECTOR(DestroyDeallocate(&vec));

	Vector& ref_to_vec = *vec;
	ref_to_vec.Length(); ref_to_vec.BLength();

	Vector vec_2;
	vec_2.Create(ref_to_vec);
	vec_2.Destroy();

	Vector vec;
	VECTOR(vec.Create(0.0F, 0.0F, 0.0F));
	VECTOR(vec.Destroy());

	Vector3F vec;
	vec.X = 0.0F;
	vec.Y = 0.0F;
	vec.Z = 0.0F;

	Vector3F* vec;
	AllocateCreate(&vec);
	Vector3F& ob = *vec;
	ob.X = 0.0F; ob.Y = 0.0F; ob.Z = 0.0F;
	DestroyDeallocate(&vec);





	// Vector_ob -> TODO: Destroy;
	Vector strob;
	VECTOR(Create_Vector(&strob));
	VECTOR(Destroy_Vector(&strob));

	// Vector_ref -> TODO: Deallocate;
	Vector* clsob;
	VECTOR(Allocate_Vector(&clsob));
	VECTOR(Deallocate_Vector(&clsob));

	Window window = Window("eMGine", 1280, 720);
	window.Main();

}
