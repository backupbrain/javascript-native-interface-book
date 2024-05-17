#include "exampleJsiLibrary.h"
#include <iostream>
#include <random>
#include <thread>
#include <dispatch/dispatch.h>

using namespace facebook::jsi;
using namespace std;

string sayHello()
{
    return "Hello world";
}

string getUserNameFromIdNative(Runtime &runtime, string userId)
{
    string name;
    if (userId == "123")
    {
        name = "John";
    }
    else if (userId == "124")
    {
        name = "Jane";
    }
    else
    {
        throw JSError(runtime, "User not found");
    }
    return name;
}

int get_random_number(int low, int high)
{
    random_device random_number_generator;
    mt19937 picker(random_number_generator());
    uniform_int_distribution<> distribution(low, high);
    int random_number = distribution(picker);
    return random_number;
}

namespace MyJsiNamespace
{
    void installExampleJsiLibrary(Runtime &runtime)
    {
        cout << "Installing library" << endl;
        const char *functionName = "simplePrint";
        // const unsigned long functionNameLength = 11; // strlen(functionName);
        // PropNameID propNameId = PropNameID::forAscii(runtime, "simplePrint", 11);
        auto propId = PropNameID::forAscii(runtime, "simplePrint");
        const int long numArguments = 0;
        HostFunctionType lambdaFunction = [](
                                              Runtime &rt,
                                              const Value &thisValue,
                                              const Value *args,
                                              size_t count) -> Value
        {
            string hello = sayHello();
            String s = String::createFromUtf8(rt, hello);
            return Value(rt, s);
        };

        /**
         * Chapter 4:
         * Accepts No Parameters and Returns Void
         */
        Function gcd = Function::createFromHostFunction(
            runtime,
            propId,
            numArguments,
            lambdaFunction);
        runtime.global().setProperty(runtime, functionName, gcd);

        Function simplePrintFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "simplePrint"),
            0, // <- zero parameters
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                // execute code here
                cout << "Hello World" << endl;
                return Value::undefined();
            });
        runtime.global().setProperty(
            runtime,
            "simplePrint",
            simplePrintFunc);

        /**
         * Chapter 5:
         * Accepts No Parameters and Returns a String
         */
        Function returnStringFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "returnString"),
            0,
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                // return a `Value` that represents a string
                return Value(
                    runtime,
                    // create a string from UTF-8 text
                    String::createFromUtf8(runtime, "Hello World"));
            });

        // register the function as callable
        runtime.global().setProperty(
            runtime,
            "returnString",
            returnStringFunc);

        /**
         * Chapter 6:
         * Accepts No Parameters and Returns number or undefined
         */
        Function numOrUndef = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "getNumberOrUndefined"),
            0, // <- zero parameters
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                // create a random number 0 or 1
                random_device rd;                         // Get random number from hardware
                mt19937 gen(rd());                        // Seed the generator
                uniform_int_distribution<> distrib(0, 1); // set range
                int randomNumber = distrib(gen);          // random [0..1]
                if (randomNumber % 2 == 0)
                {
                    return Value::undefined();
                }
                else
                {
                    return Value(37);
                }
            });

        runtime.global().setProperty(
            runtime,
            "getNumberOrUndefined",
            numOrUndef);

        /**
         * Chapter 7:
         * Accepts Primitive Type Parameters
         */
        Function getArgumentType = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "getArgumentType"),
            1, // <- 1 parameter
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                const Value &argument = arguments[0];
                string argumentType;
                if (argument.isBool())
                {
                    argumentType = "boolean";
                }
                else if (argument.isNull())
                {
                    argumentType = "null";
                }
                else if (argument.isString())
                {
                    argumentType = "string";
                }
                else if (argument.isNumber())
                {
                    argumentType = "number";
                }
                else if (argument.isObject())
                {
                    argumentType = "object";
                }
                else if (argument.isUndefined())
                {
                    argumentType = "undefined";
                }
                String argumentTypeString = String::createFromUtf8(runtime, argumentType);
                return Value(runtime, argumentTypeString);
            });

        runtime.global().setProperty(
            runtime,
            "getArgumentType",
            getArgumentType);

        /**
         * Chapter 8:
         * Accepts Multiple Parameters
         */
        Function sumFuntion = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "sum"),
            2, // <- 2 parameters
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                if (count != 2)
                {
                    throw JSError(runtime, "Invalid argument count");
                }
                double total = 0;
                for (int i = 0; i < count; i++)
                {
                    total += arguments[i].getNumber();
                }
                return Value(total);
            });

        runtime.global().setProperty(
            runtime,
            "sum",
            sumFuntion);

        /**
         * Chapter 9:
         * Return an array
         */
        Function listFruitFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "listFruit"),
            0, // <- 0 parameters
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                std::vector<std::string> fruit = {
                    "apple", "banana", "kiwi", "cherry"};
                Array jsiFruitArray(runtime, fruit.size());
                for (size_t i = 0; i < fruit.size(); ++i)
                {
                    // Convert each std::string to a JSI String
                    jsiFruitArray.setValueAtIndex(
                        runtime,
                        i,
                        String::createFromUtf8(runtime, fruit[i]));
                }

                return Value(runtime, jsiFruitArray);
            });

        runtime.global().setProperty(
            runtime,
            "listFruit",
            listFruitFunc);

        /**
         * Chapter 10:
         * Return an array
         */
        Function getPersonFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "getPerson"),
            0, // <- 0 parameters
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                // get the first argument as a string
                string id = arguments[0].asString(runtime).utf8(
                    runtime);
                // return null if id the id isn’t "123"
                if (id != "123")
                {
                    return Value();
                }
                // build an object
                Object personObject(runtime);
                String name = String::createFromUtf8(runtime, "John Doe");
                int age = 32;
                String gender = String::createFromUtf8(runtime, "male");
                // set the object properties
                personObject.setProperty(runtime, "id", id);
                personObject.setProperty(runtime, "name", name);
                personObject.setProperty(runtime, "age", age);
                personObject.setProperty(runtime, "gender", gender);
                // return the object
                return Value(runtime, personObject);
            });

        runtime.global().setProperty(
            runtime,
            "getPerson",
            getPersonFunc);

        /**
         * Chapter 11:
         * Accepts Mixed Types for a Parameter
         */
        Function optionalTypeFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "mixedParameter"),
            1, // <- 1 parameter
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                string argumentType;
                if (count == 0)
                {
                    cout << "parameter was not defined" << endl;
                    argumentType = "undefined";
                }
                else
                {
                    // get the argument as a reference to a jsi::Value
                    const Value &argument = arguments[0];
                    if (argument.isString())
                    {
                        string strVal = argument.asString(runtime).utf8(runtime);
                        cout << "parameter was a string: " << strVal << endl;
                        argumentType = "string";
                    }
                    else if (argument.isUndefined())
                    {
                        cout << "parameter was undefined" << endl;
                        argumentType = "undefined";
                    }
                    else
                    {
                        throw JSError(runtime, "Invalid argument type");
                    }
                }
                String argumentTypeString = String::createFromUtf8(runtime, argumentType);
                return Value(runtime, argumentTypeString);
            });

        runtime.global().setProperty(
            runtime,
            "mixedParameter",
            optionalTypeFunc);

        /**
         * Chapter 12:
         * Accepts objects as a parameter
         */
        Function logPersonFunction = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "logPerson"),
            1, // <- 1 parameter
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                const Object &person = arguments[0].asObject(runtime);
                string id = person.getProperty(
                                      runtime, "id")
                                .asString(runtime)
                                .utf8(runtime);
                string name = person.getProperty(
                                        runtime, "name")
                                  .asString(runtime)
                                  .utf8(runtime);
                string gender = person.getProperty(
                                          runtime, "gender")
                                    .asString(runtime)
                                    .utf8(runtime);
                int age = static_cast<int>(
                    person.getProperty(runtime, "age").asNumber());
                cout << "Person " << name << " is a " << gender << ", ";
                cout << age << " years old" << endl;
                string stringAge = std::to_string(age);
                String retVal = String::createFromUtf8(runtime, "Person " + name + " is a " + gender + ", " + stringAge + " years old");
                return Value(runtime, retVal);
            });

        runtime.global().setProperty(
            runtime,
            "logPerson",
            logPersonFunction);

        /**
         * Chapter 13:
         * Accepts arrays as parameters
         */
        Function logFruitArrayFunction = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "logFruitArray"),
            1, // <- 1 parameter
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                // Get the JSI Array from the Value
                const Array &fruit = arguments[0].asObject(runtime).asArray(runtime);
                // Get the length of the arra
                size_t length = fruit.size(runtime);
                cout << length << " fruit found:" << endl;
                // Iterate over the array element
                for (size_t i = 0; i < length; ++i)
                {
                    // Get the i-th element in the array
                    const Value &element = fruit.getValueAtIndex(runtime, i);
                    // Convert the JSI String to std::string, add it to vector
                    string fruitName = element.asString(runtime).utf8(
                        runtime);
                    // log to console
                    cout << "- " << fruitName << endl;
                }
                int numFruit = static_cast<int>(length);
                return Value(numFruit);
            });

        runtime.global().setProperty(
            runtime,
            "logFruitArray",
            logFruitArrayFunction);

        /**
         * Chapter 14:
         * Return a Promise
         */
        Function getPersonAsyncFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "getPersonNameAsync"),
            1, // <- 1 parameter
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                Function promiseConstructor = runtime.global()
                                                  .getPropertyAsFunction(runtime, "Promise");
                Value promise = promiseConstructor.callAsConstructor(
                    runtime, Function::createFromHostFunction(
                                 runtime, PropNameID::forAscii(runtime, "executor"),
                                 2, // resolve and reject
                                 [userId = arguments[0].asString(runtime).utf8(runtime)](
                                     Runtime &runtime, const Value &thisVal,
                                     const Value *promiseArgs, size_t count) -> Value
                                 {
                                     // get resolve and reject from the arguments
                                     const Function &resolve = promiseArgs[0].asObject(
                                                                                 runtime)
                                                                   .asFunction(runtime);
                                     const Function &reject = promiseArgs[1].asObject(
                                                                                runtime)
                                                                  .asFunction(runtime);
                                     try
                                     {
                                         string name = getUserNameFromIdNative(runtime, userId);
                                         resolve.call(
                                             runtime, String::createFromUtf8(runtime, name));
                                     }
                                     catch (const std::runtime_error &e)
                                     {
                                         reject.call(
                                             runtime, String::createFromUtf8(runtime, e.what()));
                                     }
                                     return Value::undefined();
                                 }));
                return promise;
            });

        runtime.global().setProperty(
            runtime,
            "getPersonNameAsync",
            getPersonAsyncFunc);

        /**
         * Chapter 15:
         * Return a Callback (setTimeoutNative)
         */
        Function setTimeoutFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "setTimeoutNative"),
            2, // <- 2 parameters
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                Function callback = arguments[0].asObject(runtime).asFunction(runtime);
                int timeoutMilliseconds = arguments[1].asNumber();

                // auto callback = std::make_shared<Function>(
                //     move(arguments[0].asObject(runtime).asFunction(runtime)));

                // Wrap the JSI Function in a unique_ptr to manage it properly
                // auto callback = make_unique<Function>(
                //     arguments[0].asObject(runtime).asFunction(runtime));

                // // Start and detach the thread, moving the unique_ptr to the lambda
                // thread([callback = move(callback), timeoutMilliseconds, &runtime]() mutable
                //        {
                //            this_thread::sleep_for(chrono::milliseconds(timeoutMilliseconds));
                //            // Execute the JSI function on the runtime thread
                //            // Use -> to access the Function object through unique_ptr
                //            // callback.get().call(runtime, {});
                //            runtime_thead.callOnThread(
                //                [callback = move(callback)](Runtime &runtime)
                //                {
                //                    callback->call(runtime, {});
                //                });
                //            // spacer
                //            // callback->call(runtime, {});
                //            // callback(runtime);
                //            // spacer
                //        })
                //     .detach();

                callback.call(runtime, {});
                return Value::undefined();
            });

        runtime.global().setProperty(
            runtime,
            "setTimeoutNative",
            setTimeoutFunc);

        /**
         * Chapter 16:
         * Return a Callback with parameter (setTimeoutNative)
         */
        Function randomDelayFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "randomDelay"),
            1, // <- 1 parameter
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                Function callback = arguments[0].asObject(runtime).asFunction(runtime);
                int timeoutMilliseconds = get_random_number(0, 1000);

                // auto callback = std::make_shared<Function>(
                //     move(arguments[0].asObject(runtime).asFunction(runtime)));

                // Wrap the JSI Function in a unique_ptr to manage it properly
                // auto callback = make_unique<Function>(
                //     arguments[0].asObject(runtime).asFunction(runtime));

                // // Start and detach the thread, moving the unique_ptr to the lambda
                // thread([callback = move(callback), timeoutMilliseconds, &runtime]() mutable
                //        {
                //            this_thread::sleep_for(chrono::milliseconds(timeoutMilliseconds));
                //            // Execute the JSI function on the runtime thread
                //            // Use -> to access the Function object through unique_ptr
                //            // callback.get().call(runtime, {});
                //            runtime_thead.callOnThread(
                //                [callback = move(callback)](Runtime &runtime)
                //                {
                //                    callback->call(runtime, {});
                //                });
                //            // spacer
                //            // callback->call(runtime, {});
                //            // callback(runtime);
                //            // spacer
                //        })
                //     .detach();
                const Value callbackArguments[] = {Value(timeoutMilliseconds)};
                callback.call(runtime, *callbackArguments, 1);
                return Value::undefined();
            });

        runtime.global().setProperty(
            runtime,
            "randomDelay",
            randomDelayFunc);

        /**
         * Chapter 17:
         * Throw errors
         */
        Function stringToNumberFunc = Function::createFromHostFunction(
            runtime,
            PropNameID::forAscii(runtime, "stringToNumber"),
            2, // <- 2 parameters
            [](
                Runtime &runtime,
                const Value &thisValue,
                const Value *arguments,
                size_t count) -> Value
            {
                // casting as string fails if `arguments[0]` isn’t a string
                string input = arguments[0].asString(runtime).utf8(runtime);
                try
                {
                    return Value(std::stod(input));
                }
                catch (const std::invalid_argument &e)
                {
                    // Error: input is not a valid number
                    throw JSError(
                        runtime,
                        "Input string is not a valid number");
                }
                catch (const std::out_of_range &e)
                {
                    // Error: result is out of range for a double
                    throw JSError(
                        runtime,
                        "Number is out of range");
                }
            });

        runtime.global().setProperty(
            runtime,
            "stringToNumber",
            stringToNumberFunc);
    }
}
