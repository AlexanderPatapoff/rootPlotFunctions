template <class ObjectType>
class ArrayHandler{
public:
  ObjectType * array_;
  int currentIndex_, arrayLength_;

  ArrayHandler(int length){
    array_ = new ObjectType[length];
    arrayLength_ = length;
  };
  /**
   * retreives value at an Index
   * @method GetValue
   * @param  index    Index Location
   * @return          Returns the value at the array location
   */
  ObjectType GetValue(int index){
    return array_[index];
  };

  /**
   * Function assigns a value to the array at the index indicated
   * @method AssignValue
   * @param  value       Value to be assigned
   * @param  index       Index Location
   * Does not through any exceptions TODO: add exception handlers
   */
  void AssignValue(ObjectType value,int index){
    array_[index] = value;
  };

  /**
   * This will replace the array currently stored with the array given
   * @method linkArray
   * @param  array     pointer to the array
   */
  void LinkArray( ObjectType * array){
    array_ = array;
  };
  /**
   * Add an array to the end of the array currently stored
   * @method tailArray
   * @param  array     Array to be added
   * @param  length    The length is needed of this array to manage the internals of this class
   */
  void TailArray(ObjectType * array, int length){
    ObjectType * newArray = new ObjectType[arrayLength_ + (length+1)];
    for (size_t i = 0; i <= arrayLength_; i++) {
      newArray[i]= array_[i];
    }
    for (size_t i = 0; i <= length; i++) {
      newArray[arrayLength_+i+1] = array_[i];
    }

    arrayLength_ += length+1;
    array_ = 0;
    array_ = newArray;
  };
  /**
   * {Prints the contents of the array}
   * @method PrintArray
   */
  void PrintArray(){
    for (size_t i = 0; i <= arrayLength_; i++) {
      cout << array_[i] << " , ";
    }
    cout << "end" << endl;
  };




};
