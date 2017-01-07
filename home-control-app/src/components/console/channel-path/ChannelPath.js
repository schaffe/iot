import * as React from "react";

export default class ChannelPath extends React.Component {
    constructor(props) {
        super(props);
        this.pathParts = ChannelPath._splitPath(props.pathParts);
    }

    

    static _splitPath(pathParts) {
        return pathParts.split("/");
    }
}