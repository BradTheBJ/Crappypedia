# 🗑️ Crappypedia

The Wikipedia client that absolutely nobody asked for. Honestly, we're not even sure why this exists, but here we are. It's like building a car that's just a steering wheel attached to a "Go to Wikipedia" button. We're aware it's terrible, and we're okay with that.

## What This Thing Does (Spoiler: Not Much)

You type words. We send you to Wikipedia. That's the entire feature set. No cap.

- ✅ Type in a search box
- ✅ Get redirected to Wikipedia
- ❌ Everything else

## The Brutally Honest Truth

Look, we're not going to lie to you. This thing is basically a fancy bookmark that pretends to be a search engine. Here's what it **doesn't** do:

- ❌ Check if the Wikipedia page actually exists (we're optimists, not realists)
- ❌ Validate if your search makes any sense (type "asdfghjklqwerty" - we'll still send you there with confidence)
- ❌ Handle errors gracefully (what even is error handling?)
- ❌ Care about your feelings (we barely care about ours)

We don't validate, we don't check, we don't think. We just redirect and hope for the best. It's chaos, but it's our chaos, and we've learned to love it.

## How to Run This Beautiful Disaster

### What You'll Need

- A C++ compiler (g++ works great, we're not picky)
- A terminal (the black box of doom)
- A sense of humor (mandatory)
- Low expectations (also mandatory)

### Step 1: Compile the Server

From the project root, do this magic:

```bash
g++ backend/server.cpp -o build/server.out
```

If it compiles, great! If it doesn't... well, that's on you now, isn't it?

### Step 2: Start the Server

Pick a port number (any number between 1024 and 65535 works, we're not picky):

```bash
./build/server.out 8080
```

Or whatever port floats your boat. We're flexible like that.

### Step 3: Open It in a Browser

Navigate to:

```
http://localhost:8080
```

Or whatever port you chose. We trust you to figure it out.

### Step 4: Embrace the Chaos

Type something. Click search. Get redirected. Question your life choices. All in a day's work.

## Project Structure (If You Can Call It That)

```
Crappypedia/
├── backend/
│   ├── index.html    # The "frontend" (we use quotes intentionally)
│   └── server.cpp    # The server that works... sometimes
├── frontend/
│   ├── services/
│   │   └── search.js # Does the redirecting (it's very good at it)
│   └── styles/
│       └── main.css  # Makes it look less like a crime scene
└── build/
    └── server.out    # The compiled result of our questionable choices
```

## The Philosophy

You know what? We're not trying to build the next big thing. We're building something that works (sort of) and we're honest about how terrible it is. There's something beautiful about that, right?

Right?

...Right?

## Why Does This Exist?

Your guess is as good as ours. Maybe it's:
- A learning experience (learning what NOT to do, mostly)
- A cautionary tale for future developers
- A cry for help
- Just because we could

We've accepted that this is our legacy now. A broken Wikipedia client that doesn't even check if pages exist. We're at peace with it.

## Final Words

Look, if you're here, you probably have low standards already. So you'll fit right in. Use this, don't use this, fork it, burn it, we honestly don't care. It's just code on the internet, and we're all going to die someday anyway.

Enjoy your terrible Wikipedia client. Or don't. We're not your boss. ✨

---

*Made with questionable life choices and just enough effort to make it compile.*
