# IOStreams2

## What if streams were more reusable?

Pictures this. You have a large library with many types that implement iostream overloads for serializing and
deserializing data. You've already written this logic once, and would like to reuse this now for something
else; perhaps a data serializer (json,yaml,xml,etc), or a `packet` type for networking.

But to make use of all your hard work, you now have to implement an `istream` or `ostream` interface, which
comes with a lot of additional complexity that you may not need. For a language like C++ that should have a
0-overhead policy, this comes with a lot of overhead!

This library is here to both ask and answer the question, **What if streams were more reusable?**

**Note**:
This is an experimental/prototype repository dedicated to providing possible alternatives to the current C++
iostreams.

## What problems does this solve?

The current C++ iostreams approach has various advantages in terms of its flexibility, but suffers
on its virtual-inheritance-based hierarchical design.

The drawbacks of the original design are:

- Virtual-inheritance cost (vtable lookup, increased memory footprint, etc)
- Stateful output streams. Writing from one object can affect the output of another
- Strict interface to implement. Adding a new stream type is more complicated than necessary, which decreases the
  ability to benefit from existing written stream-operators.

The benefits of the original design:

- The stream api (`<<` & `>>`) is coherent and idiomatic of C++

## Proposed (prototype) Solution

There are various possibilities that can ease the pain with writing new streams that can benefit from streaming
operators. This library introduces 2 possible ways of doing this:

### 1) Template `operator<<` and `operator>>`

Instead of providing overloads for `std::ostream& operator << ( ... )` or `std::ostream& operator >> ( ... )`,
provide an overload for either a SFINAE-enabled template operator -- or, better yet, `concept`-enabled operators.

This would provide the following benefits:

- True 0-overhead. The calls don't require virtual dispatch, and for lightweight streams can easily translate to
  lightweight calls
- SFINAE or concepts can be used to selectively enable different levels of stream conformance via composition. For example, there could
  be a difference between stateful, formatted streams like the current standard streams; or they could be simple,
  lightweight streams that only support unformatted raw output with formatted fundamental types.
- Adding a new stream is as simple as conforming to the concept you want. Write a new class, without any inheritance,
  to simply add the required `operator<<`/`operator>>` calls.

An example of this is below:

```c++
struct MyType
{
    int a;
    const char* str;
};

template<typename OStream, typename = std::enable_if_t<ios2::is_ostream<Ostream>::value>>
OStream& operator << ( Ostream& o, MyType type )
{
    return o << "{" << a << ", " << str << "}\n";
}
```

That's it; that's all that's required to write a stream that works with a SFINAE-enabled type.
But it gets better than that. With C++20's concepts, this becomes even cleaner:

```c++
template<OStream Stream>
Stream& operator << ( Stream& o, MyType type )
{
    ...
}
```
That's much cleaner now; no explicit SFINAE required.


This solution works well for types that have classes defined entirely within headers, but it doesn't work well for
libraries using PIMPL, or anything trying to encapsulate implementations strictly in the `*.cpp` files. But this
is still solvable!

### 2) Type-erased `any_ostream`/`any_istream`

For hiding implementations, a non-owning type-erased `any_ostream`/`any_istream` type can be used on the API boundary
to erase the concrete type between the header and implementation.

This requires building a custom vtable of all the available functions; a cost that current-day C++ streams already
require in today's implementation when it is used from a base class.