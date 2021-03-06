let component = ReasonReact.statelessComponent("ImmutableRenderer");

let make = (~state: AppState.appState, ~dispatch, _children) => {
  let incrementIfOdd =
      (store: Reductive.Store.t(ReduxThunk.thunk(AppState.appState), AppState.appState)) =>
    switch (Reductive.Store.getState(store)) {
    | {counter} when counter mod 2 === 1 =>
      Reductive.Store.dispatch(store, TimeTravelStore.CounterAction(SimpleStore.Increment))
    | _ => ()
    };
  let incrementAsync = (store) =>
    ignore(
      Js.Global.setTimeout(
        () =>
          Reductive.Store.dispatch(store, TimeTravelStore.CounterAction(SimpleStore.Increment)),
        1000
      )
    );
  {
    ...component,
    render: (_self) =>
      <div>
        <div> (ReasonReact.string("string: " ++ state.notACounter)) </div>
        <div> (ReasonReact.string("counter: " ++ string_of_int(state.counter))) </div>
        <button onClick=((_) => dispatch(TimeTravelStore.CounterAction(SimpleStore.Increment)))>
          (ReasonReact.string("Increment"))
        </button>
        <button onClick=((_) => dispatch(TimeTravelStore.CounterAction(SimpleStore.Decrement)))>
          (ReasonReact.string("Decrement"))
        </button>
        <button onClick=((_) => dispatch(TimeTravelStore.StringAction(TimeTravelStore.A)))>
          (ReasonReact.string("add a"))
        </button>
        <button onClick=((_) => dispatch(ReduxThunk.Thunk(incrementAsync)))>
          (ReasonReact.string("Increment Async"))
        </button>
        <button onClick=((_) => dispatch(ReduxThunk.Thunk(incrementIfOdd)))>
          (ReasonReact.string("Increment if Odd"))
        </button>
        <button onClick=((_) => dispatch(TimeTravelStore.TravelBackward))>
          (ReasonReact.string("Undo"))
        </button>
        <button onClick=((_) => dispatch(TimeTravelStore.TravelForward))>
          (ReasonReact.string("Redo"))
        </button>
      </div>
  }
};
