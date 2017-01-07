import React, {Component} from 'react';
import './App.css';
import Console from './console/Console';

function Indicator(props) {
    return (
        <div className="conditions_temperature">
            <span>{props.id}</span>
            <span className="value">{props.value}</span>
        </div>
    );
}

class App extends Component {
    render() {
        return (
            <div className="App">
                <div className="curtains">
                    <h2 className="curtains_title">Curtains</h2>
                    <button className="curtains_button curtains_button__open">Open</button>
                    <button className="curtains_button curtains_button__close">Close</button>
                    <button className="curtains_button curtains_button__open">Stop</button>
                </div>

                <div className="conditions">
                    <h2 className="conditions_title">Conditions</h2>
                    <Indicator id="temperature" value="15"/>
                </div>

                <div className="channel">
                    <div className="channel_name channel_name__blue">&nbsp;</div>
                    <div className="channel_arrow channel_arrow__blue"></div>
                </div>
                <div className="channel">
                    <div className="channel_name channel_name__red">room</div>
                    <div className="channel_arrow channel_arrow__red "></div>
                </div>
                <div className="channel">
                    <div className="channel_name channel_name__blue">room</div>
                    <div className="channel_arrow channel_arrow__blue"></div>
                </div>
                <Console/>
            </div>
        );
    }
}

export default App;
