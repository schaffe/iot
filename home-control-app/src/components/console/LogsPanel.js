import * as React from "react";
import './LogsPanel.css';

export default class LogsPanel extends React.Component {

    // constructor(props) {
    //     super(props);
    // }

    render() {
        return (
            <div id="logs-panel" className={this.props.hide ? "logs-panel hide" : "logs-panel"}>
                <div className="filters">
                    <span className="filters_item">Temperature</span>
                    <span className="filters_item">Humidity</span>
                    <span className="filters_item">Curtains</span>
                </div>
                <div className="logs"></div>
            </div>
        );
    }
}
