import './Application.css';
import Console from './components/console/Console';
import * as React from "react";

function Indicator(props) {
    return (
        <div className="conditions_temperature">
            <span>{props.id}</span>
            <span className="value">{props.value}</span>
        </div>
    );
}

export default class Application extends React.Component {
    render() {
        return (
            <div>
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