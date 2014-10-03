template<typedef T>
class PriorityQueue
{
	public:
		PriorityQueue<T>(int size);
		~PriorityQueue<T>();

		int push(T priority);
		int pop();

		T fetch(int index);

		bool isEmpty();

	private:
		T* priorities;
		const int SIZE;
};
