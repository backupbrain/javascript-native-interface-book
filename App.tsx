import React, {useState} from 'react';
import {
  Button,
  SafeAreaView,
  ScrollView,
  StatusBar,
  StyleSheet,
  Text,
  View,
} from 'react-native';
import {Colors} from 'react-native/Libraries/NewAppScreen';

type Person = {
  id: string;
  name: string;
  age: number;
  gender: 'male' | 'female';
};

// https://mariusschulz.com/blog/declaring-global-variables-in-typescript
declare global {
  function simplePrint(): void;
  function returnString(): string;
  function getNumberOrUndefined(): number | undefined;
  function getArgumentType(
    param: string | number | boolean | undefined | null,
  ): string;
  function sum(param1?: number, param2?: number): number;
  function listFruit(): string[];
  function getPerson(personId: string): Person;
  function mixedParameter(param?: string | undefined): string;
  function logPerson(person: Person): string;
  function logFruitArray(fruit: string[]): number;

  function getPersonNameAsync(personId: string): Promise<string>;
  function setTimeoutNative(callback: () => void, timeout: number): void;
  function randomDelay(callback: (praam: string) => void): void;

  function stringToNumber(value: string): number;
}

function App(): React.JSX.Element {
  const [returnStringResult, setReturnStringResult] = useState('');
  const [numberOrUndefinedResult, setNumberOrUndefinedResult] = useState<
    number | undefined
  >(undefined);
  const [argumentType, setArgumentType] = useState('');
  const [sumValue, setSumValue] = useState<number | undefined>(undefined);
  const [arrayValue, setArrayValue] = useState<string[]>([]);
  const [personValue, setPersonValue] = useState<Person | null>(null);
  const [mixedParameterValue, setMixedParameterValue] = useState<
    string | undefined
  >(undefined);
  const [logPersonValue, setLogPersonValue] = useState('');
  const [logFruitValue, setLogFruitValue] = useState<number | undefined>(
    undefined,
  );
  const [callbackActivated, setCallbackActivated] = useState(false);
  const [parameterCallbackValue, setParameterCallbackValue] = useState('');
  const [personName, setPersonName] = useState('');
  const [stringToNumberValue, setStringToNumberValue] = useState<
    string | number
  >('');

  const backgroundStyle = {
    backgroundColor: Colors.lighter,
  };

  const onSimplePrintPress = () => {
    simplePrint();
  };

  const onReturnStringPress = () => {
    const result = returnString();
    setReturnStringResult(result);
  };

  const onNumOrUndefinedPress = () => {
    const result: number | undefined = getNumberOrUndefined();
    console.log(result);
    setNumberOrUndefinedResult(result);
  };

  const onGetArgumentTypePress = (
    value: string | null | undefined | boolean | number,
  ) => {
    const result = getArgumentType(value);
    console.log(result);
    setArgumentType(result);
  };

  const onSumPress = () => {
    const result = sum(1, 2);
    console.log(result);
    setSumValue(result);
  };

  const onArrayPress = () => {
    const result = listFruit();
    console.log(result);
    setArrayValue(result);
  };

  const onGetPersonPress = (personId: string) => {
    const result = getPerson(personId);
    console.log(result);
    setPersonValue(result);
  };

  const onMixedParameterPress = (param?: string | undefined) => {
    const result = mixedParameter(param);
    console.log(result);
    setMixedParameterValue(result);
  };

  const onLogPersonPress = () => {
    const person: Person = {
      id: '123',
      name: 'John Doe',
      age: 30,
      gender: 'male',
    };
    const result = logPerson(person);
    console.log(result);
    setLogPersonValue(result);
  };

  const onLogFruitPress = () => {
    const fruit: string[] = ['apple', 'banana', 'cherry', 'date', 'elderberry'];
    const result = logFruitArray(fruit);
    console.log(result);
    setLogFruitValue(result);
  };

  const onAsyncPress = async (personId: string) => {
    const result = await getPersonNameAsync(personId);
    console.log(result);
    setPersonName(result);
  };

  const onCallbackPress = () => {
    setTimeoutNative(() => {
      console.log('Callback function is called');
      setCallbackActivated(true);
      setTimeout(() => {
        setCallbackActivated(false);
      }, 1000);
    }, 1000);
  };

  const onCallbackWithParmsPress = () => {
    randomDelay((param: string) => {
      console.log(`Callback response: ${param}`);
      setParameterCallbackValue(param);
    });
  };

  const onStringToNumberPress = (value: any) => {
    try {
      const result = stringToNumber(value);
      console.log(result);
      setStringToNumberValue(result);
    } catch (error: any) {
      console.error(error);
      setStringToNumberValue(error.message);
    }
  };

  return (
    <SafeAreaView style={backgroundStyle}>
      <StatusBar
        barStyle={'dark-content'}
        backgroundColor={backgroundStyle.backgroundColor}
      />
      <ScrollView
        contentInsetAdjustmentBehavior="automatic"
        style={backgroundStyle}>
        <View
          style={{
            backgroundColor: Colors.white,
          }}>
          <View style={styles.chapterRow}>
            <Text>Chapter 4: Simple Print</Text>
            <View style={styles.horizontal}>
              <Button title="Press" onPress={onSimplePrintPress} />
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 5: Return a String</Text>
            <View style={styles.horizontal}>
              <Button title="Press" onPress={onReturnStringPress} />
              <Text>Result: {returnStringResult}</Text>
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 6: Return a number or undefined</Text>
            <View style={styles.horizontal}>
              <Button title="Press" onPress={onNumOrUndefinedPress} />
              <Text>Result: {numberOrUndefinedResult || 'undefined'}</Text>
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 7: Accept a primitive parameter</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press for true"
                onPress={() => {
                  onGetArgumentTypePress(true);
                }}
              />
              <Button
                title="Press for hello"
                onPress={() => {
                  onGetArgumentTypePress('hello');
                }}
              />
              <Button
                title="Press for 123"
                onPress={() => {
                  onGetArgumentTypePress(123);
                }}
              />
              <Button
                title="Press for null"
                onPress={() => {
                  onGetArgumentTypePress(null);
                }}
              />
              <Button
                title="Press for undefined"
                onPress={() => {
                  onGetArgumentTypePress(undefined);
                }}
              />
              <Text>Result: {argumentType}</Text>
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 8: Accept multiple parameters</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press"
                onPress={() => {
                  onSumPress();
                }}
              />
              <Text>Result: {sumValue}</Text>
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 9: Return an array</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press"
                onPress={() => {
                  onArrayPress();
                }}
              />
              <Text>Result: {arrayValue.join(', ')}</Text>
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 10: Return an object</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press for person 123"
                onPress={() => {
                  onGetPersonPress('123');
                }}
              />
              <Button
                title="Press for null person"
                onPress={() => {
                  onGetPersonPress('124');
                }}
              />
              <Text>
                Result:{' '}
                {personValue
                  ? `${personValue.name} is ${personValue.age} years old`
                  : 'null'}
              </Text>
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 11: Mixed Parameters</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press for string argument"
                onPress={() => {
                  onMixedParameterPress('example');
                }}
              />
              <Button
                title="Press for undefined argument"
                onPress={() => {
                  onMixedParameterPress(undefined);
                }}
              />
              <Button
                title="Press for empty argument"
                onPress={() => {
                  onMixedParameterPress();
                }}
              />
              <Text>
                Result:{' '}
                {mixedParameterValue ? mixedParameterValue : 'undefined'}
              </Text>
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 12: Accept an object</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press"
                onPress={() => {
                  onLogPersonPress();
                }}
              />
              <Text>Result: {logPersonValue}</Text>
            </View>
          </View>
          <View style={styles.chapterRow}>
            <Text>Chapter 13: Accept an array</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press"
                onPress={() => {
                  onLogFruitPress();
                }}
              />
              <Text>
                Result: {logFruitValue ? logFruitValue + ' fruit logged' : ''}
              </Text>
            </View>
          </View>

          <View style={styles.chapterRow}>
            <Text>Chapter 14: Return a Promise</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press for person 123"
                onPress={() => {
                  onAsyncPress('123');
                }}
              />
              <Button
                title="Press for person 124"
                onPress={() => {
                  onAsyncPress('124');
                }}
              />
              <Text>Result: {personName}</Text>
            </View>
          </View>

          <View style={styles.chapterRow}>
            <Text>Chapter 15: Callback Function</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press"
                onPress={() => {
                  onCallbackPress();
                }}
              />
              <Text>
                Callback Activated: {callbackActivated ? 'Yes' : 'Not yet'}
              </Text>
            </View>
          </View>

          <View style={styles.chapterRow}>
            <Text>Chapter 15: Callback Function with parameters</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press"
                onPress={() => {
                  onCallbackWithParmsPress();
                }}
              />
              <Text>Callback Activated: {parameterCallbackValue}</Text>
            </View>
          </View>

          <View style={styles.chapterRow}>
            <Text>Chapter 17: Throw an error</Text>
            <View style={styles.horizontal}>
              <Button
                title="Press for number"
                onPress={() => {
                  onStringToNumberPress('123');
                }}
              />
              <Button
                title="Press for non-number"
                onPress={() => {
                  onStringToNumberPress(null);
                }}
              />
              <Text>Result: {stringToNumberValue}</Text>
            </View>
          </View>
        </View>
      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  highlight: {
    fontWeight: '700',
  },
  chapterRow: {
    justifyContent: 'flex-start',
    marginBottom: 10,
  },
  horizontal: {
    flexDirection: 'row',
    justifyContent: 'flex-start',
    gap: 10,
  },
});

export default App;
