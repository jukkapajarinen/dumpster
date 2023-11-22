const initialState = {
  drawerState: 'closed'
};

const GeneralReducer = (state = initialState, action) => {
  switch (action.type) {
    case 'GENERAL_OPEN_DRAWER':
      return {...state, drawerState: 'opened'};
    case 'GENERAL_CLOSE_DRAWER':
      return {...state, drawerState: 'closed'};
    default:
      return state;
  }
};

export default GeneralReducer;
