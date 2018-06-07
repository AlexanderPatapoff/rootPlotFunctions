template <class ObjectType>
class ArrayHandler{
public:
  ObjectType * array;
  int currentIndex, arrayLength;

  ArrayHandler(int length){
    array = new ObjectType[length];
    arrayLength = length;
  };

  ObjectType GetValue(int index){
    return array[index];
  };

  void AssignValue(ObjectType value,int index){
    array[index] = value;
  };

};
