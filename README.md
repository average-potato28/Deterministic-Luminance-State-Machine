# Deterministic-Luminance-State-Machine

An ultra-low-latency, bare-metal asynchronous state machine for the STM32F4xx. The project implements a fully non-blocking temporal sequencer utilizing highly optimized SysTick hardware interrupts to achieve deterministic hardware-level execution. By leveraging custom memory-mapped peripheral manipulation and Phase-Locked Loop (PLL) clock synthesis.

## Features

* **Clock Synthesis:** Implements custom SystemClock_Config protocols to awaken the High-Speed External (HSE) oscillator, driving the core logic through a Phase-Locked Loop (PLL) multiplexer to achieve a blistering 100MHz system core clock execution rate.
* **Asynchronous Sequencing:** Eliminates legacy blocking delays by utilizing a volatile utick hardware-timer architecture. This allows the CPU to execute parallel instruction streams while deterministically calculating state-change boundaries.
* **Memory-Mapped Peripheral Mutation:** Bypasses high-level abstraction layers by directly manipulating raw silicon memory addresses (e.g., 0x424102B4u) via bit-banding aliases, ensuring absolute minimum-latency state toggling of the GPIO interfaces.
* **Race-Condition Safe Memory Swapping:** Utilizes localized static memory allocation during active-low and active-high phase transitions to securely swap luminance frequency variables without triggering shared-resource race conditions.

## Bugs Faced & Mitigated

During the development of this bare-metal sequencer, several critical embedded systems challenges were encountered and resolved through architectural design choices:

1. **CPU Starvation via Delay Loops:**
   * **Challenge:** Standard delays completely blocked the CPU execution pipeline.
   * **Mitigation:** Engineered a non-blocking `delay()` state-evaluator utilizing a hardware-driven `utick` counter. This allows the main execution loop to remain unblocked during LED state transitions.

2. **Compiler Aggressive Optimization (ISR Failures):**
   * **Challenge:** The cross-compiler optimized out the background SysTick increments, trapping the logic in an infinite loop.
   * **Mitigation:** Applied the `volatile` qualifier to the global `utick` variable, enforcing strict memory fetches and securing variables modified inside the hardware interrupt service routine.

3. **Memory Corruption during Data Swaps:**
   * **Challenge:** Rapidly swapping luminance cycle arrays risked shared resource race conditions and stack memory volatility.
   * **Mitigation:** Implemented a secure `swap` function utilizing statically allocated arrays to return localized memory safely, executing only after verifying structural safety against race conditions.

4. **Premature Execution Faults:**
   * **Challenge:** Instructing the peripheral logic before the high-speed clock synthesis finalized caused silicon hard faults.
   * **Mitigation:** Built strict polling verification into the `SystemClock_Config` protocol, holding execution via `while(LL_RCC_PLL_IsReady() != 1)` until the clock domains achieved absolute stability.

5. **GPIO Read-Modify-Write Latency:**
   * **Challenge:** Standard register toggling introduced multi-cycle latency, opening the door for hardware interrupts to corrupt the GPIO states.
   * **Mitigation:** Transitioned from ODR logic to atomic memory manipulation via bit-banding aliases (e.g., `0x424102B4u`), allowing instantaneous state toggling with zero read-modify-write overhead.

## Hardware Setup & Architecture

Here is the physical wiring and component breakdown for the state machine:

![ST-Link V2](assets/stlinkv2.jpeg)
![STM32](assets/stm32.jpeg)
![Logic Analyzer](assets/logic_analyser.jpeg)
![Wiring Diagram](assets/wiring.jpeg)

### Clock Configuration

To achieve the 100MHz system core clock execution rate, the PLL multiplexer was configured as follows:

![Clock Tree Schematic](assets/clock.png)

## Empirical Proof

Below is a capture of the debugger verifying the non-blocking state transitions in real-time:

![Pulse View Output](assets/pulseview1.jpeg)
<video src="https://raw.githubusercontent.com/average-potato28/Deterministic-Luminance-State-Machine/main/assets/debugger1.mp4" controls="controls" width="100%"></video>