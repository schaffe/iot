import * as React from "react";
import './Console.css';
import LogsPanel from "./LogsPanel";

class Console extends React.Component {

    constructor(props) {
        super(props);
        this.state = {
            isConsoleHidden: false
        };
        this.onHideConsoleClick = this.onHideConsoleClick.bind(this);
    }

    onHideConsoleClick() {
        this.setState(prevState => ({
            isConsoleHidden: !prevState.isConsoleHidden
        }));
    }

    render() {
        return (
            <div className="console">
                <LogsPanel hide={this.state.isConsoleHidden}/>
                <div className="command">
                    <button className="switcher" onClick={this.onHideConsoleClick}>O</button>
                    <select className="command_channel">
                        <option>/kitchen/fridge/listeun</option>
                        <option>/room/curtains/listen</option>
                    </select>
                    <input type="text" className="command_text"/>
                </div>
            </div>
        );
    }
}
export default Console;
