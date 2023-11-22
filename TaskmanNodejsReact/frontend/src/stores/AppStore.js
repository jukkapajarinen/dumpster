import { createConnectedStore, withLogger } from 'undux';

const store = createConnectedStore({
  menuOpen: false,
  loggedIn: false,
  username: '',
  userId: -1,
  email: '',
  lists: [{ id: 0, name: '', priority: 0 }],
  tasks: [{ id: 0, listid: 0, name: '', priority: 0, state: 0 }],
  listActive: 0,
  tasksActive: [{ id: 0, listid: 0, name: '', priority: 0, state: 0 }]
}, withLogger);

export default store;