import React, { Component } from 'react';

class Projects extends Component {
  render() {
    return (
      <section className="section has-text-centered-mobile" id="projects-section">
        <div className="container">
          <h2 className="title">{ this.props.data.title }</h2>
          <h3 className="subtitle">{ this.props.data.subTitle }</h3>
          {this.props.data.items.map((project, i) => 
            <a className="columns" href={ project.link } key={ i }>
              <div className="column">{this.props.data.project} {project.index}: {project.name} </div>
              <div className="column tags has-text-right has-text-centered-mobile">
                {project.tags.map((tag, j) => 
                  <span className="tag is-light" key={ j }>{ tag }</span>
                )}
              </div>
            </a>
          )}
        </div>
      </section>
    )
  }
}

export default Projects;