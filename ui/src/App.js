import axios from 'axios';
import React from 'react';
import logo from './logo.svg';
import bulbOn from './bulb-on.png';
import bulbOff from './bulb-off.png';

import './App.css';

class App extends React.Component {
  state = {
    word: "reading",
    isOn: false,
    counting: 0,
    intervalId: 0
  }
  async componentDidMount() {
    // const intervalId = setInterval(this.fetching, 1000);
    // this.setState({ intervalId: intervalId });
    this.fetching()
  }
  componentWillUnmount() {
    // use intervalId from the state to clear the interval
    clearInterval(this.state.intervalId);
  }
  fetching = async () => {
    // if (this.state.counting % 10 == 0) {
    const { data } = await axios.get('http://0a603569.ngrok.io/');
    console.log(data)
    let isOn;
    if (data.result.includes(2)) isOn = true;
    else if (data.result.includes(1)) isOn = this.state.isOn;
    else isOn = false;
    // const productList = productword.data
    this.setState({ word: data.word, isOn, counting: this.state.counting + 1 })
    // } else {
    //   this.setState({ counting: this.state.counting + 1 })
    // }

  }

  render() {
    return (
      <div className="App" >
        <header className="App-header">
          <p>
            {/* {this.state.counting % 3 == 0 && '.'}
            {this.state.counting % 3 == 1 && '..'}
            {this.state.counting % 3 == 2 && '...'} */}
            {this.state.word}
            {/* {this.state.counting % 3 == 0 && '.'}
            {this.state.counting % 3 == 1 && '..'}
            {this.state.counting % 3 == 2 && '...'} */}
          </p>
          {this.state.isOn && <img src={bulbOn} className="App-logo" alt="logo" />}
          {!this.state.isOn && <img src={bulbOff} className="App-logo" alt="logo" />}
        </header>
      </div>
    );
  }
}


export default App;
