template<class T>
class vectori{
	T **myarr;
	int _size, maxsize;
public:
	vectori(){
		maxsize = 20;
		_size = 0;
		myarr = (T**)malloc(maxsize*sizeof(T));
	}
	vectori(int ms){
		maxsize = ms;
		_size = 0;
		myarr = (T**)malloc(ms*sizeof(T));
	}
	void push_back(T k){
		if (_size == maxsize){
			T **newpointer = (T**)malloc(maxsize * 2 * sizeof(T*));
			for (int i = 0; i < _size; i++)
				newpointer[i] = myarr[i];
			maxsize *= 2;
			free(myarr);
			myarr = newpointer;


		}
		myarr[_size] = (T*)malloc(sizeof(T));
		*myarr[_size++] = k;


	}
	T &operator[] (int idx){
		return *myarr[idx];
	}
	int size(){
		return _size;
	}
	void clear(){
		T **newpointer = (T**)malloc(maxsize  * sizeof(T*));
		for (int i = 0; i < _size; i++)
			newpointer[i] = myarr[i];
		//free(myarr);
		myarr = newpointer;
		_size = 0;
	}
	void delete_ele(int pos){
		if (pos >= _size)
			return;
		else{
			int i = 0;
			for (i = pos; i < _size - 1; i++){
				myarr[i] = myarr[i + 1];
			}
			_size -= 1;
		}
	}
	void pop_front(){
		if (_size == 0)
			return;
		else{
			int i = 0;
			for (i = 0; i < _size - 1; i++){
				myarr[i] = myarr[i + 1];
			}
			_size -= 1;

		}
	}


};